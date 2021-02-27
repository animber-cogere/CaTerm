#include <caterm/system/detail/user_input_event_loop.hpp>

#include <caterm/system/event_queue.hpp>
#include <caterm/terminal/terminal.hpp>
#include <caterm/widget/widget.hpp>

namespace ox::detail {

auto User_input_event_loop::run() -> int
{
    return loop_.run(
        [](Event_queue& q) { q.append(ox::Terminal::read_input()); });
}

}  // namespace ox::detail
