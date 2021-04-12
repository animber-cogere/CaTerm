#ifndef CATERM_WIDGET_WIDGETS_WRITE_FILE_HPP
#define CATERM_WIDGET_WIDGETS_WRITE_FILE_HPP
#include <fstream>

#include <signals_light/signal.hpp>

#include <caterm/painter/color.hpp>
#include <caterm/widget/pipe.hpp>
#include <caterm/widget/tuple.hpp>
#include <caterm/widget/widgets/button.hpp>
#include <caterm/widget/widgets/textline.hpp>
#include <caterm/widget/widgets/tile.hpp>

namespace ox::detail {

struct Write_file_widgets : HTuple<Button, Tile, Textline> {
    Button& save_btn        = this->get<0>();
    Tile& buffer            = this->get<1>();
    Textline& filename_edit = this->get<2>();

    Write_file_widgets()
        : HTuple<Button, Tile, Textline>{{U"Save"}, {U'>'}, {U"Filename"}}
    {
        using namespace ox::pipe;
        *this | fixed_height(1);
        save_btn | fixed_width(4) | bg(Color::Blue);
        filename_edit | bg(Color::White) | fg(Color::Black) |
            ghost(Color::Dark_gray);
    }
};

}  // namespace ox::detail

namespace ox {

template <typename Char_t = char>
class Write_file : public detail::Write_file_widgets {
   public:
    using Stream_t = std::basic_ofstream<Char_t>;

    struct Parameters {};

   public:
    sl::Signal<void(Stream_t&)> request;

   public:
    Write_file()
    {
        save_btn | pipe::on_press([this] { this->notify(); });
    }

    Write_file(Parameters) : Write_file{} {}

   private:
    void notify()
    {
        auto ofs = Stream_t{filename_edit.contents().str()};
        request.emit(ofs);
    }
};

/// Helper function to create an instance.
template <typename Char_t = char>
[[nodiscard]] inline auto write_file() -> std::unique_ptr<Write_file<Char_t>>
{
    return std::make_unique<Write_file<Char_t>>();
}

}  // namespace ox
#endif  // CATERM_WIDGET_WIDGETS_WRITE_FILE_HPP
