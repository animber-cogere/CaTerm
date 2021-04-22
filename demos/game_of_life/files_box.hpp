#ifndef CATERM_DEMOS_GAME_OF_LIFE_FILES_BOX_HPP
#define CATERM_DEMOS_GAME_OF_LIFE_FILES_BOX_HPP
#include <string>

#include <signals_light/signal.hpp>

#include <caterm/painter/color.hpp>
#include <caterm/widget/layouts/vertical.hpp>
#include <caterm/widget/pipe.hpp>
#include <caterm/widget/widgets/confirm_button.hpp>
#include <caterm/widget/widgets/line.hpp>
#include <caterm/widget/widgets/textline.hpp>

#include "colors.hpp"

namespace gol {

/// Provides interface to input filename and to Signal on that filename.
class File_widget : public ox::layout::Vertical<> {
   public:
    struct Parameters {
        std::u32string btn_text;
    };

   public:
    ox::Textline& filename_box_ = this->make_child<ox::Textline>(U"Filename");

    ox::Confirm_button& confirm_btn_;

    sl::Signal<void(std::string const&)> file_request;

   public:
    explicit File_widget(Parameters parameters)
        : confirm_btn_{
              this->make_child<ox::Confirm_button>(parameters.btn_text)}
    {
        using namespace ox;
        using namespace ox::pipe;

        *this | fixed_height(2);

        confirm_btn_ | on_press([this]() {
            file_request(filename_box_.contents().str());
        });

        confirm_btn_.main_btn | bg(color::Teal) | fg(color::White);
        confirm_btn_.confirm_page.confirm_btn | bg(color::Light_green) |
            fg(color::Black);
        confirm_btn_.confirm_page.exit_btn | bg(color::Teal) | fg(color::White);
    }
};

struct Files_box : ox::VTuple<File_widget, File_widget, ox::HLine> {
   public:
    File_widget& import_btn = this->get<0>();
    File_widget& export_btn = this->get<1>();
    ox::HLine& break_       = this->get<2>() | fg(color::Teal);

   public:
    sl::Signal<void(std::string const&)>& import_request =
        import_btn.file_request;

    sl::Signal<void(std::string const&)>& export_request =
        export_btn.file_request;

   public:
    Files_box()
        : ox::VTuple<File_widget, File_widget, ox::HLine>{{U"Import"},
                                                          {U"Export"},
                                                          {}}
    {
        *this | ox::pipe::fixed_height(5);
    }
};

}  // namespace gol
#endif  // CATERM_DEMOS_GAME_OF_LIFE_FILES_BOX_HPP
