#ifndef CATERM_DEMOS_PALETTE_VALUE_CONTROL_HPP
#define CATERM_DEMOS_PALETTE_VALUE_CONTROL_HPP
#include <signals_light/signal.hpp>

#include <caterm/painter/glyph_string.hpp>
#include <caterm/widget/layouts/horizontal.hpp>
#include <caterm/widget/layouts/vertical.hpp>
#include <caterm/widget/pipe.hpp>
#include <caterm/widget/tuple.hpp>
#include <caterm/widget/widgets/label.hpp>
#include <caterm/widget/widgets/slider.hpp>
#include <caterm/widget/widgets/textline.hpp>

namespace palette::detail {

/// Slider_bottom with extra space around the sides.
struct Buffered_slider : ox::HTuple<ox::Widget, ox::Slider_bottom, ox::Widget> {
    Widget& left              = this->get<0>() | ox::pipe::fixed_width(1);
    ox::Slider_bottom& slider = this->get<1>();
    Widget& right             = this->get<2>() | ox::pipe::fixed_width(1);

    Buffered_slider()
        : ox::HTuple<ox::Widget, ox::Slider_bottom, ox::Widget>{{},
                                                                {{0, 255}, 0},
                                                                {}}
    {}
};

/// Textline with extra space on the left side.
class Buffered_edit_box : public ox::layout::Horizontal<> {
   public:
    Buffered_edit_box();

   public:
    Widget& left      = this->make_child() | ox::pipe::fixed_width(1);
    ox::Textline& box = this->make_child<ox::Textline>(U"0");
};
}  // namespace palette::detail

namespace palette {

/// Provides user interface to change a color value from [0, 255].
/** Emits signal when changed. */
class Value_control : public ox::layout::Vertical<> {
    detail::Buffered_slider& slider_{
        this->make_child<detail::Buffered_slider>()};

    detail::Buffered_edit_box& value_edit_{
        this->make_child<detail::Buffered_edit_box>()};

    ox::HLabel& label_;

   public:
    explicit Value_control(const ox::Glyph_string& label);

    /// Set the current value being held.
    void set_value(int value) { slider_.slider.set_value(value); }

    sl::Signal<void(int)>& value_changed{slider_.slider.value_changed};
};

}  // namespace palette
#endif  // CATERM_DEMOS_PALETTE_VALUE_CONTROL_HPP
