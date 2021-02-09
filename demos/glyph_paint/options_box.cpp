#include "options_box.hpp"

#include <array>
#include <utility>

#include <caterm/painter/color.hpp>
#include <caterm/painter/palette/amstrad_cpc.hpp>
#include <caterm/painter/palette/apple_ii.hpp>
#include <caterm/painter/palette/ashes.hpp>
#include <caterm/painter/palette/basic.hpp>
#include <caterm/painter/palette/basic8.hpp>
#include <caterm/painter/palette/cga.hpp>
#include <caterm/painter/palette/commodore_64.hpp>
#include <caterm/painter/palette/commodore_vic20.hpp>
#include <caterm/painter/palette/dawn_bringer16.hpp>
#include <caterm/painter/palette/dawn_bringer32.hpp>
#include <caterm/painter/palette/en4.hpp>
#include <caterm/painter/palette/gameboy.hpp>
#include <caterm/painter/palette/gameboy_pocket.hpp>
#include <caterm/painter/palette/macintosh_ii.hpp>
#include <caterm/painter/palette/msx.hpp>
#include <caterm/painter/palette/nes.hpp>
#include <caterm/painter/palette/savanna.hpp>
#include <caterm/painter/palette/secam.hpp>
#include <caterm/painter/palette/stormy6.hpp>
#include <caterm/painter/palette/teletext.hpp>
#include <caterm/painter/palette/thomson_m05.hpp>
#include <caterm/painter/palette/windows.hpp>
#include <caterm/painter/palette/windows_console.hpp>
#include <caterm/painter/palette/zx_spectrum.hpp>
#include <caterm/system/system.hpp>
#include <caterm/terminal/terminal.hpp>
#include <caterm/widget/pipe.hpp>

namespace paint {

Options_B::Options_B()
{
    using namespace ox;
    using namespace ox::pipe;

    space1 | wallpaper(U'─');
    palette_label | align_center();
    back_btn | bg(Color::Light_gray) | fg(Color::Black);
    palette_box | bg(Color::White) | fg(Color::Black);

    auto const palettes = std::array{
        std::pair{U"Dawn Bringer 16", dawn_bringer16::palette},
        std::pair{U"Dawn Bringer 32", dawn_bringer32::palette},
        std::pair{U"Basic 16", basic::palette},
        std::pair{U"Basic 8", basic8::palette},
        std::pair{U"EN 4", en4::palette},
        std::pair{U"Stormy 6", stormy6::palette},
        std::pair{U"Savanna VIM", savanna::palette},
        std::pair{U"Ashes VIM", ashes::palette},
        std::pair{U"Amstrad CPC", amstrad_cpc::palette},
        std::pair{U"Apple II", apple_ii::palette},
        std::pair{U"Macintosh II", macintosh_ii::palette},
        std::pair{U"CGA", cga::palette},
        std::pair{U"MSX", msx::palette},
        std::pair{U"SECAM", secam::palette},
        std::pair{U"Commodore 64", commodore_64::palette},
        std::pair{U"Commodore VIC-20", commodore_vic20::palette},
        std::pair{U"Gameboy", gameboy::palette},
        std::pair{U"Gameboy Pocket", gameboy_pocket::palette},
        std::pair{U"NES", nes::palette},
        std::pair{U"Teletext", teletext::palette},
        std::pair{U"Thomson M05", thomson_m05::palette},
        std::pair{U"Early Windows", windows::palette},
        std::pair{U"Windows Console", windows_console::palette},
        std::pair{U"ZX Spectrum", zx_spectrum::palette},
    };

    for (auto const& [name, palette] : palettes) {
        palette_box.add_option(name).connect(
            [p = palette] { System::terminal.set_palette(p); });
    }
}

}  // namespace paint
