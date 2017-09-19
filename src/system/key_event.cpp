#include "system/events/key_event.hpp"
#include "system/key.hpp"
#include "system/event_handler.hpp"

namespace cppurses {

// class Key_event
Key_event::Key_event(Event::Type type, Event_handler* receiver, Key key_code)
    : Input_event{type, receiver}, key_code_{key_code} {}

// class Key_press_event
Key_press_event::Key_press_event(Event_handler* receiver, Key key_code)
    : Key_event{Event::KeyPress, receiver, key_code} {}

bool Key_press_event::send() const {
    if (!receiver_->enabled()) {
        return false;
    }
    if (key_code_ == Key::Tab && Focus_system::tab_press()) {
        return true;
    }
    return receiver_->key_press_event(key_code_, key_to_char(key_code_));
}

bool Key_press_event::filter_send(Event_handler* filter) const {
    return filter->key_press_event_filter(receiver_, key_code_,
                                          key_to_char(key_code_));
}

// class Key_release_event
Key_release_event::Key_release_event(Event_handler* receiver, Key key_code)
    : Key_event{Event::KeyRelease, receiver, key_code} {}

bool Key_release_event::send() const {
    if (receiver_->enabled()) {
        return receiver_->key_release_event(key_code_, key_to_char(key_code_));
    }
    return false;
}

bool Key_release_event::filter_send(Event_handler* filter) const {
    return filter->key_release_event_filter(receiver_, key_code_,
                                            key_to_char(key_code_));
}

}  // namespace cppurses
