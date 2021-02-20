#include <caterm/system/detail/user_input_event_loop.hpp>

#include <caterm/system/event.hpp>
#include <caterm/system/system.hpp>
#include <caterm/terminal/terminal.hpp>

namespace ox::detail {

auto User_input_event_loop::run() -> int
{
    return loop_.run(
        [] { ox::System::post_event(ox::Terminal::read_input()); });
}

}  // namespace ox::detail
