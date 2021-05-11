#include <string>

#include <caterm/system/system.hpp>
#include <caterm/widget/array.hpp>
#include <caterm/widget/layouts/horizontal.hpp>
#include <caterm/widget/layouts/vertical.hpp>
#include <caterm/widget/pair.hpp>
#include <caterm/widget/pipe.hpp>
#include <caterm/widget/tuple.hpp>
#include <caterm/widget/widgets/line.hpp>
#include <caterm/widget/widgets/slider.hpp>
#include <caterm/widget/widgets/text_view.hpp>

using namespace ox;

namespace {

template <typename Slider_t>
struct Slider_view : VPair<Slider_t, Text_view> {
    Slider_view() : VPair<Slider_t, Text_view>{{{-255, 255}, 0}, {U"Init"}}
    {
        this->first.value_changed.connect(
            [this](int v) { this->second.set_text(std::to_string(v)); });
        this->second | pipe::fixed_height(1);
    }
};

}  // namespace

int main()
{
    System{Mouse_mode::Drag}
        .run<HTuple<Slider_view<Slider_top>, VLine, Slider_view<Slider_bottom>,
                    VLine, Slider_view<Slider_left>, VLine,
                    Slider_view<Slider_right>>>();
}
