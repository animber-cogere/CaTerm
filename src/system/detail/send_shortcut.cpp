#include <caterm/system/detail/send_shortcut.hpp>

#include <caterm/system/event.hpp>
#include <caterm/system/shortcuts.hpp>

namespace ox::detail {

template <>
auto send_shortcut<ox::Key_press_event>(ox::Key_press_event const& e) -> bool
{
    return ox::Shortcuts::send_key(e.key);
}

}  // namespace ox::detail
