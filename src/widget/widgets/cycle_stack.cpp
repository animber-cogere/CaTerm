#include <caterm/widget/widgets/cycle_stack.hpp>

#include <caterm/painter/color.hpp>
#include <caterm/painter/glyph_string.hpp>
#include <caterm/widget/pipe.hpp>
#include <caterm/widget/tuple.hpp>
#include <caterm/widget/widgets/button.hpp>
#include <caterm/widget/widgets/cycle_box.hpp>

namespace ox::detail {

CS_top_row::CS_top_row(Parameters)
    : HTuple<Button, Cycle_box, Button>{{U"<"}, {}, {U">"}}
{
    using namespace pipe;
    *this | fixed_height(1) | children() | bg(Color::Light_gray) |
        fg(Color::Black);

    left_btn | fixed_width(1) | on_press(slot::previous(cycle_box));
    right_btn | fixed_width(1) | on_press(slot::next(cycle_box));
    cycle_box | Trait::Bold;
}

}  // namespace ox::detail
