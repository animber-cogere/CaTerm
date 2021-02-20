#ifndef CATERM_WIDGET_WIDGETS_LOG_HPP
#define CATERM_WIDGET_WIDGETS_LOG_HPP
#include <signals_light/signal.hpp>

#include <caterm/system/key.hpp>
#include <caterm/widget/widgets/text_display.hpp>
#include <caterm/widget/widgets/textbox.hpp>

namespace ox {
class Glyph_string;

class Log : public Textbox {
   public:
    void post_message(Glyph_string message);

   protected:
    auto key_press_event(Key k) -> bool override;

    using Text_display::append;
    using Text_display::erase;
    using Text_display::insert;
    using Text_display::pop_back;
    using Text_display::set_contents;
};

/// Helper function to create an instance.
template <typename... Args>
[[nodiscard]] auto log(Args&&... args) -> std::unique_ptr<Log>
{
    return std::make_unique<Log>(std::forward<Args>(args)...);
}

}  // namespace ox

namespace ox::slot {

[[nodiscard]] auto post_message(Log& log) -> sl::Slot<void(Glyph_string)>;

[[nodiscard]] auto post_message(Log& log, Glyph_string const& message)
    -> sl::Slot<void()>;

}  // namespace ox::slot
#endif  // CATERM_WIDGET_WIDGETS_LOG_HPP
