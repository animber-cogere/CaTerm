#include <caterm/widget/widgets/write_file.hpp>

#include <caterm/painter/color.hpp>
#include <caterm/widget/pipe.hpp>
#include <caterm/widget/widgets/button.hpp>
#include <caterm/widget/widgets/line_edit.hpp>
#include <caterm/widget/widgets/tile.hpp>

namespace ox::detail {

Write_file_widgets::Write_file_widgets()
    : HTuple<Button, Tile, Line_edit>{
          {U"Save"},
          {U'>'},
          {U"Filename" | fg(Color::Dark_gray), ox::Align::Left,
           ox::Line_edit::Action::Clear}}
{
    using namespace ox::pipe;
    *this | fixed_height(1);
    save_btn | fixed_width(4) | bg(Color::Blue);
    filename_edit | bg(Color::White) | fg(Color::Black);
}

}  // namespace ox::detail
