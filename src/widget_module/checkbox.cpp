#include "widget_module/widgets/checkbox.hpp"
#include "painter_module/painter.hpp"
#include "widget_module/size_policy.hpp"

namespace twf {

Checkbox::Checkbox() {
    this->geometry().size_policy().horizontal_policy = Size_policy::Fixed;
    this->geometry().set_width_hint(2);
    this->geometry().size_policy().vertical_policy = Size_policy::Fixed;
    this->geometry().set_height_hint(1);
}

bool Checkbox::paint_event(const Paint_event& event) {
    Painter p{this};
    if (checked_) {
        p.put(checked_box_);
    } else {
        p.put(empty_box_);
    }
    return Widget::paint_event(event);
}

bool Checkbox::mouse_press_event(const Mouse_event& event) {
    if (event.button() == Mouse_button::Left) {
        this->toggle();
        this->update();
    }
    return true;
}

void Checkbox::toggle() {
    checked_ = !checked_;
    toggled();
    checked_ ? checked() : unchecked();
}

}  // namespace twf
