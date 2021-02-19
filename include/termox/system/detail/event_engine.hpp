#ifndef CATERM_SYSTEM_DETAIL_EVENT_ENGINE_HPP
#define CATERM_SYSTEM_DETAIL_EVENT_ENGINE_HPP
#include <cassert>
#include <memory>
#include <mutex>

#include <caterm/common/lockable.hpp>
#include <caterm/painter/detail/is_paintable.hpp>
#include <caterm/painter/detail/screen.hpp>
#include <caterm/painter/detail/staged_changes.hpp>
#include <caterm/system/detail/event_queue.hpp>
#include <caterm/system/event.hpp>
#include <caterm/system/system.hpp>
#include <caterm/widget/area.hpp>
#include <caterm/widget/point.hpp>

namespace ox::detail {

/// Orchestrates all event processing and queueing.
class Event_engine : public Lockable<std::recursive_mutex> {
   public:
    /// Invokes events and flush the screen.
    void process()
    {
        auto const lock = this->Lockable::lock();
        if (queue_.send_all())  // if any events sent
            flush_screen();
    }

    /// Adds the given event to the Event_queue
    void append(Event e)
    {
        auto const lock = this->Lockable::lock();
        queue_.append(std::move(e));
    }

   private:
    /// Flushes all of the staged changes to the screen and sets the cursor.
    static void flush_screen()
    {
        System::terminal.show_cursor(false);
        System::terminal.refresh();
        // Cursor
        Widget const* const fw = System::focus_widget();
        if (fw != nullptr && is_paintable(*fw)) {
            assert(is_within(fw->cursor.position(), fw->area()));
            System::set_cursor(fw->cursor, fw->inner_top_left());
        }
    }

    /// Return true if \p point is within \p area.
    [[nodiscard]] static auto is_within(Point point, Area area) -> bool
    {
        return point.x < area.width && point.y < area.height;
    }

   private:
    Event_queue queue_;
};

}  // namespace ox::detail
#endif  // CATERM_SYSTEM_DETAIL_EVENT_ENGINE_HPP
