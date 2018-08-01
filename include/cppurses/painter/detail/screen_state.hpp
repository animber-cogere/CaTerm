#ifndef CPPURSES_PAINTER_DETAIL_SCREEN_STATE_HPP
#define CPPURSES_PAINTER_DETAIL_SCREEN_STATE_HPP
#include <cppurses/painter/detail/screen_descriptor.hpp>
#include <cppurses/painter/detail/staged_changes.hpp>
#include <cppurses/painter/paint_buffer.hpp>

namespace cppurses {
namespace detail {

/// Holds a Screen_descriptor representing the current screen state of a Widget.
///
/// Widget is the owner of this object, but only the flush function can modify
/// its state.
class Screen_state {
    Screen_descriptor tiles;
    friend void Paint_buffer::flush(const Staged_changes&);
};

}  // namespace detail
}  // namespace cppurses
#endif  // CPPURSES_PAINTER_DETAIL_SCREEN_STATE_HPP
