#ifndef CATERM_WIDGET_WIDGETS_CYCLE_STACK_HPP
#define CATERM_WIDGET_WIDGETS_CYCLE_STACK_HPP
#include <memory>
#include <type_traits>
#include <utility>

#include <caterm/painter/brush.hpp>
#include <caterm/painter/color.hpp>
#include <caterm/painter/glyph_string.hpp>
#include <caterm/painter/trait.hpp>
#include <caterm/widget/layouts/horizontal.hpp>
#include <caterm/widget/layouts/stack.hpp>
#include <caterm/widget/layouts/vertical.hpp>
#include <caterm/widget/pair.hpp>
#include <caterm/widget/pipe.hpp>
#include <caterm/widget/tuple.hpp>
#include <caterm/widget/widget.hpp>
#include <caterm/widget/widgets/button.hpp>
#include <caterm/widget/widgets/cycle_box.hpp>

namespace ox::detail {

/// User interface to cycle through the pages of the Stack.
class CS_top_row : public HTuple<Button, Cycle_box, Button> {
   public:
    Button& left_btn     = this->get<0>();
    Cycle_box& cycle_box = this->get<1>();
    Button& right_btn    = this->get<2>();

   public:
    CS_top_row() : HTuple<Button, Cycle_box, Button>{{U"<"}, {}, {U">"}}
    {
        using namespace pipe;
        *this | fixed_height(1) | children() | bg(Color::Light_gray) |
            fg(Color::Black);

        left_btn | fixed_width(1) | on_press(slot::previous(cycle_box));
        right_btn | fixed_width(1) | on_press(slot::next(cycle_box));
        cycle_box | Trait::Bold;
    }
};

}  // namespace ox::detail
namespace ox {

/// A layout::Stack with an interface to cycle through each Widget in the stack.
template <typename Child = Widget>
class Cycle_stack : public VPair<detail::CS_top_row, layout::Stack<Child>> {
   public:
    struct Parameters {};

   public:
    detail::CS_top_row& top_row = this->first;
    layout::Stack<Child>& stack = this->second;

   public:
    explicit Cycle_stack(Parameters = {}) {}

   public:
    /// Construct a new Widget_t object and add it to the end of the Stack.
    /** Returns a reference to this newly created page. \p title is passed to
     *  the Cycle_box to display when this page is active. */
    template <typename Widget_t = Child, typename... Args>
    auto make_page(Glyph_string title, Args&&... args) -> Widget_t&
    {
        static_assert(std::is_base_of<Child, Widget_t>::value,
                      "Cycle_stack::make_page: Widget_t must be a Child type");
        auto child = std::make_unique<Widget_t>(std::forward<Args>(args)...);
        return static_cast<Widget_t&>(
            this->append_page(std::move(title), std::move(child)));
    }

    /// Append a page to the Stack.
    /** \p title is passed to the Cycle_box associated with this page. */
    auto append_page(Glyph_string title, std::unique_ptr<Child> widget)
        -> Child&
    {
        auto& signal = top_row.cycle_box.add_option(std::move(title));
        signal.connect(slot::set_active_page(stack, stack.size()));
        auto& child = stack.append_page(std::move(widget));
        if (stack.size() == 1)
            stack.set_active_page(0);
        return child;
    }
};

/// Helper function to create a Cycle_stack instance.
template <typename Child = Widget>
[[nodiscard]] auto cycle_stack(typename Cycle_stack<Child>::Parameters = {})
    -> std::unique_ptr<Cycle_stack<Child>>
{
    return std::make_unique<Cycle_stack<Child>>();
}

}  // namespace ox
#endif  // CATERM_WIDGET_WIDGETS_CYCLE_STACK_HPP
