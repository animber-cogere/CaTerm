#ifndef CATERM_WIDGET_WIDGETS_TITLEBAR_HPP
#define CATERM_WIDGET_WIDGETS_TITLEBAR_HPP
#include <utility>

#include <caterm/painter/color.hpp>
#include <caterm/painter/glyph_string.hpp>
#include <caterm/system/system.hpp>
#include <caterm/widget/layouts/horizontal.hpp>
#include <caterm/widget/pipe.hpp>
#include <caterm/widget/size_policy.hpp>
#include <caterm/widget/widgets/button.hpp>
#include <caterm/widget/widgets/label.hpp>

namespace ox {

/// Provides a centered title and flush-right exit button.
/** The exit button will call System::quit() when pressed. Titlebar is fixed at
 *  a height of 1. */
class Titlebar : public layout::Horizontal<> {
   public:
    HLabel& title;
    Button& exit_button;

   public:
    /// Construct a Titlebar with centered \p title.
    explicit Titlebar(Glyph_string title_ = "")
        : title{this->make_child<HLabel>(
              {std::move(title_), Align::Center, extra_left, extra_right})},
          exit_button{this->make_child<Button>(U"│✕ ")}
    {
        using namespace ox::pipe;
        *this | fixed_height(1);
        *this | children() | bg(Color::White) | fg(Color::Black);
        exit_button | fixed_width(exit_width) | on_press(System::quit);
    }

   private:
    inline static auto constexpr exit_width  = 3;
    inline static auto constexpr extra_left  = 0;
    inline static auto constexpr extra_right = exit_width;
};

/// Helper function to create an instance.
template <typename... Args>
auto titlebar(Args&&... args) -> std::unique_ptr<Titlebar>
{
    return std::make_unique<Titlebar>(std::forward<Args>(args)...);
}

}  // namespace ox
#endif  // CATERM_WIDGET_WIDGETS_TITLEBAR_HPP
