#ifndef CATERM_DEMOS_ANIMATION_ANIMATED_WIDGET_HPP
#define CATERM_DEMOS_ANIMATION_ANIMATED_WIDGET_HPP
#include <caterm/painter/color.hpp>
#include <caterm/painter/glyph.hpp>
#include <caterm/painter/painter.hpp>
#include <caterm/system/mouse.hpp>
#include <caterm/widget/layouts/horizontal.hpp>
#include <caterm/widget/pipe.hpp>
#include <caterm/widget/point.hpp>
#include <caterm/widget/widget.hpp>

namespace demos::animation {

/// Box containing a circle character that bounces off the Widget's walls.
class Animated_box : public ox::Widget {
   public:
    /// Initialize with the frames-per-second the animation will happen in.
    explicit Animated_box(ox::FPS fps) : fps_{fps}
    {
        *this | ox::pipe::strong_focus();
    }

   protected:
    auto timer_event() -> bool override
    {
        flip_increment(xy_.x, x_direction_, this->width());
        flip_increment(xy_.y, y_direction_, this->height());
        this->update();
        return Widget::timer_event();
    }

    auto paint_event(ox::Painter& p) -> bool override
    {
        p.put(glyph_, xy_);
        return Widget::paint_event(p);
    }

    auto enable_event() -> bool override
    {
        this->enable_animation(fps_);
        return Widget::enable_event();
    }

    auto disable_event() -> bool override
    {
        this->disable_animation();
        return Widget::disable_event();
    }

    auto mouse_press_event(const ox::Mouse& m) -> bool override
    {
        xy_ = m.at;
        this->update();
        return Widget::mouse_press_event(m);
    }

    auto resize_event(ox::Area new_size, ox::Area old_size) -> bool override
    {
        reset(xy_.x, this->width());
        reset(xy_.y, this->height());
        return Widget::resize_event(new_size, old_size);
    }

   private:
    ox::FPS const fps_;

    ox::Glyph glyph_ = U'○' | fg(ox::Color::Yellow);
    ox::Point xy_    = ox::Point{0, 0};
    int x_direction_ = 1;
    int y_direction_ = 1;

   private:
    /// Increments by \p direction, if 0 or \p max, flips the direction.
    /** \p limit is one past the last viable value. */
    static void flip_increment(int& value, int& direction, int limit)
    {
        if (limit == 1)
            return;
        if ((direction == -1 && value == 0) ||
            (direction == +1 && value + 1 == limit)) {
            direction *= -1;
        }
        value += direction;
    }

    /// Adjust a coord if the borders have moved so that it is out of bounds.
    /** \p limit is one past the last viable value. */
    static void reset(int& value, int limit)
    {
        if (value >= limit)
            value = (limit == 0 ? 0 : limit - 1);
    }
};

/// Contains a few Animated_boxes at various animation rates.
inline auto build_demo() -> std::unique_ptr<ox::Widget>
{
    using namespace ox;
    auto app = layout::horizontal<Animated_box>(
        std::make_unique<Animated_box>(FPS{5}),
        std::make_unique<Animated_box>(FPS{10}) | pipe::bordered(),
        std::make_unique<Animated_box>(FPS{20}),
        std::make_unique<Animated_box>(FPS{30}) | pipe::bordered(),
        std::make_unique<Animated_box>(FPS{60}));
    app | pipe::direct_focus() | pipe::on_focus_in([x = app.get()] {
        ox::System::set_focus(x->get_children().front());
    });
    return app;
}

}  // namespace demos::animation
#endif  // CATERM_DEMOS_ANIMATION_ANIMATED_WIDGET_HPP
