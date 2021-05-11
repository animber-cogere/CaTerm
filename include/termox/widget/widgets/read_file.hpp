#ifndef CATERM_WIDGET_WIDGETS_READ_FILE_HPP
#define CATERM_WIDGET_WIDGETS_READ_FILE_HPP
#include <fstream>
#include <memory>

#include <signals_light/signal.hpp>

#include <caterm/widget/pipe.hpp>
#include <caterm/widget/tuple.hpp>
#include <caterm/widget/widgets/button.hpp>
#include <caterm/widget/widgets/line_edit.hpp>
#include <caterm/widget/widgets/tile.hpp>

namespace ox::detail {

struct Read_file_widgets : HTuple<Button, Tile, Line_edit> {
    Button& open_btn         = this->get<0>();
    Tile& buffer             = this->get<1>();
    Line_edit& filename_edit = this->get<2>();

    Read_file_widgets();
};

}  // namespace ox::detail

namespace ox {

/// Provides a filename Line_edit and button to emit a std::ifstream.
template <typename Char_t = char>
class Read_file : public detail::Read_file_widgets {
   public:
    using Stream_t = std::basic_ifstream<Char_t>;

    struct Parameters {};

   public:
    sl::Signal<void(Stream_t&)> request;

   public:
    Read_file()
    {
        open_btn | pipe::on_press([this] { this->notify(); });
    }

    Read_file(Parameters) : Read_file{} {}

   private:
    void notify()
    {
        auto ifs = Stream_t{filename_edit.text().str()};
        request.emit(ifs);
    }
};

/// Helper function to create a Read_file instance.
template <typename Char_t = char>
[[nodiscard]] auto read_file() -> std::unique_ptr<Read_file<Char_t>>
{
    return std::make_unique<Read_file<Char_t>>();
}

}  // namespace ox
#endif  // CATERM_WIDGET_WIDGETS_READ_FILE_HPP
