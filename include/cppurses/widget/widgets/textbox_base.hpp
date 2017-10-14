#ifndef WIDGET_WIDGETS_TEXTBOX_BASE_HPP
#define WIDGET_WIDGETS_TEXTBOX_BASE_HPP
#include "painter/glyph_string.hpp"
#include "widget/coordinates.hpp"
#include "widget/widgets/text_display.hpp"

#include <signals/signal.hpp>

#include <cstddef>

namespace cppurses {

class Textbox_base : public Text_display {
   public:
    explicit Textbox_base(Glyph_string contents = "");

    // Scrolling
    void scroll_up(std::size_t n = 1) override;
    void scroll_down(std::size_t n = 1) override;
    void enable_scrolling(bool enable = true);
    void disable_scrolling(bool disable = true);
    void toggle_scrolling();

    // Cursor Movement
    void cursor_up(std::size_t n = 1);
    void cursor_down(std::size_t n = 1);
    void cursor_left(std::size_t n = 1);
    void cursor_right(std::size_t n = 1);
    void set_cursor(Coordinates pos);
    void set_cursor(std::size_t x, std::size_t y);
    void set_cursor(std::size_t index);

    // Query Functions
    bool does_scroll() const { return scroll_; }
    std::size_t cursor_index() const;

    // Signals
    sig::Signal<void(std::size_t n)> cursor_moved_left;
    sig::Signal<void(std::size_t n)> cursor_moved_right;
    sig::Signal<void(std::size_t n)> cursor_moved_up;
    sig::Signal<void(std::size_t n)> cursor_moved_down;
    sig::Signal<void(Coordinates)> cursor_moved;

   private:
    void increment_cursor_right();
    void increment_cursor_left();
    bool scroll_{true};

   protected:
    bool resize_event(std::size_t new_width,
                      std::size_t new_height,
                      std::size_t old_width,
                      std::size_t old_height) override;
};

}  // namespace cppurses
#endif  // WIDGET_WIDGETS_TEXTBOX_BASE_HPP
