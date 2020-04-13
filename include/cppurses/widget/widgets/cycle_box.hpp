#ifndef CPPURSES_WIDGET_WIDGETS_CYCLE_BOX_HPP
#define CPPURSES_WIDGET_WIDGETS_CYCLE_BOX_HPP
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

#include <signals/signals.hpp>

#include <cppurses/painter/glyph.hpp>
#include <cppurses/painter/glyph_string.hpp>
#include <cppurses/system/events/key.hpp>
#include <cppurses/system/events/mouse.hpp>
#include <cppurses/widget/detail/tracks_lifetime.hpp>
#include <cppurses/widget/focus_policy.hpp>
#include <cppurses/widget/layouts/horizontal.hpp>
#include <cppurses/widget/pipe.hpp>
#include <cppurses/widget/widgets/cycle_box.hpp>
#include <cppurses/widget/widgets/label.hpp>
#include <cppurses/widget/widgets/tile.hpp>

// TODO Indicate in focus with color or trait change.
namespace cppurses {

/// A rotating set of labels, emitting a Signal when the label is changed.
/** Labels are cycled forwards by a left click or scroll up, cycled backwards
 *  by a scroll down button press, or arrow keys. */
class Cycle_box : public Label {
   public:
    /// Emitted when the option is changed, sends the new option's string rep.
    sig::Signal<void(std::string)> option_changed;

   public:
    Cycle_box() { *this | pipe::align_center() | pipe::strong_focus(); }

    /// Add an option/label to the Cycle_box.
    /** The returned Signal reference will be emitted every time this option is
     *  enabled. \p label's string representation is the identifying param. */
    auto add_option(Glyph_string label) -> sig::Signal<void()>&
    {
        options_.emplace_back(std::move(label));
        if (this->size() == 1)
            this->set_current_option(0);
        return options_.back().enabled;
    }

    /// Remove an option/label identified by its text.
    /** No-op if does no match found. Only removes the first option found if
     *  there are multiple options with identical text. */
    void remove_option(Glyph_string const& label)
    {
        auto const& label_str = label.str();
        if (label_str == this->current_option_label().str())
            this->set_current_option(0);
        auto const iter = this->find(label_str);
        if (iter != std::end(options_))
            options_.erase(iter);
    }

    /// Move forward one option.
    void next();

    /// Move backward one option.
    void previous();

    /// Set the current option to the option with \p label identifier.
    /** Does not emit the option's signal. No-op if label is not an option. */
    void set_current_option(std::string const& label)
    {
        auto const iter = this->find(label);
        if (iter != std::end(options_))
            this->set_current_option(std::distance(std::begin(options_), iter));
    }

    /// Set the current option to the one at \p index.
    /** Does not emit the option's signal.
     * Input Constraints: \p index < options_.size() */
    void set_current_option(std::size_t index)
    {
        index_ = index;
        *this | pipe::contents(options_[index_].name);
    }

    /// Return the number of options in the Cycle_box.
    auto size() const -> std::size_t { return options_.size(); }

   protected:
    auto mouse_press_event(Mouse::State const& mouse) -> bool override
    {
        switch (mouse.button) {
            case Mouse::Button::Left: this->next(); break;
            case Mouse::Button::Right: this->previous(); break;
            default: break;
        }
        return Label::mouse_press_event(mouse);
    }

    auto mouse_wheel_event(Mouse::State const& mouse) -> bool override
    {
        switch (mouse.button) {
            case Mouse::Button::ScrollDown: this->next(); break;
            case Mouse::Button::ScrollUp: this->previous(); break;
            default: break;
        }
        return Label::mouse_wheel_event(mouse);
    }

    auto key_press_event(Key::State const& keyboard) -> bool override
    {
        switch (keyboard.key) {
            case Key::Arrow_up:
            case Key::k: this->previous(); break;
            case Key::Arrow_down:
            case Key::j: this->next(); break;
            default: break;
        }
        return Label::key_press_event(keyboard);
    }

   private:
    /// Holds an Option's Signal and name.
    struct Option {
        explicit Option(Glyph_string name_) : name{std::move(name_)} {}
        Glyph_string name;
        sig::Signal<void()> enabled;
    };
    std::vector<Option> options_;
    std::size_t index_ = 0uL;

   private:
    /// Return the current option's text.
    auto current_option_label() const -> Glyph_string
    {
        if (options_.empty())
            return "";
        return options_[index_].name;
    }

    /// Find iter into options_ that points to label, else end iter.
    auto find(std::string const& label) -> decltype(options_)::iterator
    {
        auto const begin = std::begin(options_);
        auto const end   = std::end(options_);
        return std::find_if(begin, end, [&label](Option const& opt) {
            return opt.name == label;
        });
    }

    /// Emit both the option_changed signal and the current option's signal.
    void emit_signals()
    {
        this->option_changed(this->current_option_label().str());
        options_[index_].enabled();  // This is a signal.
    }
};

/// A label on the left and a Cycle_box on the right.
class Labeled_cycle_box : public layout::Horizontal<> {
   public:
    Label& label         = this->make_child<Label>();
    Tile& div            = this->make_child<Tile>(L'├');
    Cycle_box& cycle_box = this->make_child<Cycle_box>();

   public:
    explicit Labeled_cycle_box(Glyph_string title = "")
    {
        *this | pipe::fixed_height(1) | pipe::label(std::move(title));
    }

    void set_label(Glyph_string title)
    {
        label.set_contents(std::move(title));
        this->resize_label();
    }

    void set_divider(Glyph divider) { div.set(divider); }

   private:
    void resize_label()
    {
        label | pipe::fixed_width(label.contents().size() + 1);
    }
};

namespace slot {

inline auto add_option(Cycle_box& cb) -> sig::Slot<void(Glyph_string)>
{
    return tracks_lifetime(
        cb, [&cb](Glyph_string label) { cb.add_option(std::move(label)); });
}

inline auto add_option(Cycle_box& cb, Glyph_string const& label)
    -> sig::Slot<void()>
{
    return tracks_lifetime(cb, [&cb, label] { cb.add_option(label); });
}

inline auto remove_option(Cycle_box& cb) -> sig::Slot<void(std::string const&)>
{
    return tracks_lifetime(
        cb, [&cb](std::string const& label) { cb.remove_option(label); });
}

inline auto remove_option(Cycle_box& cb, std::string const& label)
    -> sig::Slot<void()>
{
    return tracks_lifetime(cb, [&cb, label] { cb.remove_option(label); });
}

inline auto next(Cycle_box& cb) -> sig::Slot<void()>
{
    return tracks_lifetime(cb, [&cb]() { cb.next(); });
}

inline auto previous(Cycle_box& cb) -> sig::Slot<void()>
{
    return tracks_lifetime(cb, [&cb]() { cb.previous(); });
}

}  // namespace slot
}  // namespace cppurses
#endif  // CPPURSES_WIDGET_WIDGETS_CYCLE_BOX_HPP
