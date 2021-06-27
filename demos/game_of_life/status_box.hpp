#ifndef CATERM_DEMOS_GAME_OF_LIFE_STATUS_BOX_HPP
#define CATERM_DEMOS_GAME_OF_LIFE_STATUS_BOX_HPP
#include <cstdint>

#include <caterm/painter/glyph_string.hpp>
#include <caterm/widget/align.hpp>
#include <caterm/widget/layouts/horizontal.hpp>
#include <caterm/widget/layouts/vertical.hpp>
#include <caterm/widget/pair.hpp>
#include <caterm/widget/widgets/label.hpp>
#include <caterm/widget/widgets/line.hpp>
#include <caterm/widget/widgets/line_edit.hpp>
#include <caterm/widget/widgets/number_edit.hpp>
#include <caterm/widget/widgets/number_view.hpp>
#include <caterm/widget/widgets/text_view.hpp>

#include "colors.hpp"

namespace gol {

class Generation_count : public ox::HPair<ox::HLabel, ox::Int_view> {
   public:
    Generation_count()
        : ox::HPair<ox::HLabel, ox::Int_view>{{U"Generation"}, {0}}
    {
        using namespace ox::pipe;
        *this | fixed_height(1) | hide_cursor();
        title_ | fixed_width(11);
        count_ | fixed_width(5);
    }

   public:
    void update_count(std::uint32_t count) { count_.set_value(count); }

   private:
    ox::HLabel& title_   = this->first;
    ox::Int_view& count_ = this->second;
};

struct Coord_view : ox::HPair<ox::HLabel, ox::Int_edit> {
    struct Parameters {
        ox::Glyph_string label;
    };

    ox::HLabel& label  = this->first;
    ox::Int_edit& edit = this->second;

    Coord_view(Parameters parameters)
        : ox::HPair<ox::HLabel, ox::Int_edit>{{parameters.label},
                                              {0, {-1'000, 1'000}}}
    {
        using namespace ox::pipe;
        label | dynamic_growth();
        edit | bg(color::Black) | fg(color::White);
    }
};

struct Center_offset : ox::VTuple<ox::HLabel, Coord_view, Coord_view> {
   public:
    ox::HLabel& title_   = this->get<0>();
    Coord_view& x_coords = this->get<1>();
    Coord_view& y_coords = this->get<2>();

   public:
    Center_offset()
        : ox::VTuple<ox::HLabel, Coord_view, Coord_view>{
              {U"Center Offset" | ox::Trait::Underline},
              {U"x: "},
              {U"y: "}}
    {
        title_ | ox::pipe::align_center();
    }
};

struct Status_box : ox::VTuple<Generation_count, ox::HLine, Center_offset> {
   public:
    Generation_count& gen_count  = this->get<0>();
    ox::HLine& break_            = this->get<1>() | fg(color::Teal);
    Center_offset& center_offset = this->get<2>();

   public:
    Status_box() { *this | ox::pipe::fixed_height(5); }
};

}  // namespace gol
#endif  // CATERM_DEMOS_GAME_OF_LIFE_STATUS_BOX_HPP
