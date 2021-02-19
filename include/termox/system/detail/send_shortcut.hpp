#ifndef CATERM_SYSTEM_DETAIL_SEND_SHORTCUT_HPP
#define CATERM_SYSTEM_DETAIL_SEND_SHORTCUT_HPP
#include <caterm/system/event.hpp>
#include <caterm/system/shortcuts.hpp>

namespace ox::detail {

template <typename T>
[[nodiscard]] auto send_shortcut(T const&) -> bool
{
    return false;
}

template <>
[[nodiscard]] inline auto send_shortcut<ox::Key_press_event>(
    ox::Key_press_event const& e) -> bool
{
    return ox::Shortcuts::send_key(e.key);
}

}  // namespace ox::detail
#endif  // CATERM_SYSTEM_DETAIL_SEND_SHORTCUT_HPP
