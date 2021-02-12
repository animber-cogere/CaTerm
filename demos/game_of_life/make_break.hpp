#ifndef CATERM_DEMOS_GAME_OF_LIFE_MAKE_BREAK_HPP
#define CATERM_DEMOS_GAME_OF_LIFE_MAKE_BREAK_HPP
#include <memory>

#include <caterm/widget/pipe.hpp>
#include <caterm/widget/widget.hpp>

#include "colors.hpp"

namespace gol {

inline auto make_break() -> std::unique_ptr<ox::Widget>
{
    using namespace ox::pipe;
    return ox::widget() | fixed_height(1) | wallpaper(U'─' | fg(color::Teal));
}

}  // namespace gol
#endif  // CATERM_DEMOS_GAME_OF_LIFE_MAKE_BREAK_HPP
