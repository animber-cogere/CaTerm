#ifndef CPPURSES_WIDGET_CURSOR_DATA_HPP
#define CPPURSES_WIDGET_CURSOR_DATA_HPP
#include <cstddef>

#include <signals/signal.hpp>

#include <cppurses/widget/point.hpp>

namespace cppurses {
class Widget;

/// Holds and provides access to all data relevant to a Widget's cursor.
class Cursor_data {
   public:
    /// Signal called when the cursor is moved, passing along the new position.
    sig::Signal<void(Point)> moved;

   public:
    explicit Cursor_data(Widget const* owner) : owner_{owner} {}

    /// Query if the cursor is enabled.
    auto enabled() const -> bool { return enabled_; }

    /// Get the local x coordinate of the cursor.
    auto x() const -> std::size_t { return position_.x; }

    /// Get the local y coordinate of the cursor.
    auto y() const -> std::size_t { return position_.y; }

    /// Get the local position of the cursor.
    auto position() const -> Point { return position_; }

    /// Enable the cursor(show on screen).
    void enable(bool enable = true) { enabled_ = enable; }

    /// Disable the cursor(do not show on screen).
    void disable(bool disable = true) { this->enable(!disable); }

    /// Enable the cursor if disabled, or disable it if enabled.
    void toggle() { this->enable(!this->enabled()); }

    /// Set the local x coordinate of the cursor.
    void set_x(std::size_t x);

    /// Set the local y coordinate of the cursor.
    void set_y(std::size_t y);

    /// Set the local position of the cursor.
    void set_position(Point p)
    {
        this->set_x(p.x);
        this->set_y(p.y);
    }

   private:
    Point position_ = {0, 0};
    bool enabled_   = false;
    Widget const* owner_;
};

}  // namespace cppurses
#endif  // CPPURSES_WIDGET_CURSOR_DATA_HPP
