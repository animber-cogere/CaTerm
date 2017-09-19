#ifndef SYSTEM_EVENTS_CLOSE_EVENT_HPP
#define SYSTEM_EVENTS_CLOSE_EVENT_HPP
#include "system/event.hpp"

namespace cppurses {
class Widget;

class Close_event : public Event {
   public:
    explicit Close_event(Widget* receiver);
    bool send() const override;
    bool filter_send(Widget* filter_widget) const override;
};

}  // namespace cppurses
#endif  // SYSTEM_EVENTS_CLOSE_EVENT_HPP
