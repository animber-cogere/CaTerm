#include <caterm/system/detail/user_input_event_loop.hpp>

#include <caterm/system/event.hpp>
#include <caterm/system/system.hpp>
#include <caterm/terminal/terminal.hpp>

namespace ox::detail {

void User_input_event_loop::loop_function()
{
    ox::System::post_event(ox::System::terminal.get());
}

}  // namespace ox::detail
