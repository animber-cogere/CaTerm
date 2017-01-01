#ifndef INPUT_EVENT_HPP
#define INPUT_EVENT_HPP

#include "../event.hpp"

namespace twf {

class Input_event : public Event {
   public:
    enum class KeyboardModifiers { None };

   protected:
    explicit Input_event(Event::Type type)
        : Event{type}, modifiers_{KeyboardModifiers::None} {}
    KeyboardModifiers modifiers_;
};

}  // namespace twf
#endif  // INPUT_EVENT_HPP
