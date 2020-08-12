#include <cppurses/terminal/terminal.hpp>

#include <algorithm>
#include <chrono>
#include <clocale>
#include <csignal>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <iterator>
#include <mutex>
#include <stdexcept>

#ifndef _XOPEN_SOURCE_EXTENDED
#    define _XOPEN_SOURCE_EXTENDED
#endif
#include <ncursesw/ncurses.h>
#undef border

#include <cppurses/painter/color.hpp>
#include <cppurses/painter/palette/basic.hpp>
#include <cppurses/painter/palette/basic8.hpp>
#include <cppurses/painter/palette/dawn_bringer16.hpp>
#include <cppurses/system/system.hpp>
#include <cppurses/terminal/input.hpp>
#include <cppurses/terminal/terminal_error.hpp>
#include <cppurses/widget/widget.hpp>

extern "C" void handle_sigint(int /* sig*/)
{
    cppurses::System::terminal.uninitialize();
#if !defined __APPLE__ && !defined __MINGW32__
    std::quick_exit(0);
#else
    std::exit(0);
#endif
}

namespace {
using namespace cppurses;

auto scale(RGB::Value_t value) -> short
{
    auto constexpr value_max   = RGB::Value_t{255};
    auto constexpr ncurses_max = short{1000};
    return static_cast<short>((static_cast<double>(value) / value_max) *
                              ncurses_max);
}

}  // namespace

namespace cppurses {

void Terminal::initialize()
{
    if (is_initialized_)
        return;
    std::setlocale(LC_ALL, "en_US.UTF-8");

    if (::newterm(std::getenv("TERM"), stdout, stdin) == nullptr and
        ::newterm("xterm-256color", stdout, stdin) == nullptr) {
        throw std::runtime_error{"Unable to initialize screen."};
    }
    std::signal(SIGINT, &handle_sigint);

    is_initialized_ = true;
    ::noecho();
    ::keypad(::stdscr, true);
    ::set_escdelay(1);
    ::mousemask(ALL_MOUSE_EVENTS, nullptr);
    ::mouseinterval(0);
    this->set_refresh_rate(refresh_rate_);
    if (this->has_color()) {
        ::start_color();
        try {
            this->set_palette(dawn_bringer16::palette);
        }
        catch (Terminal_error const&) {
            if (this->has_extended_colors())
                this->set_palette(basic::palette);
            else
                this->set_palette(basic8::palette);
        }
    }
    this->ncurses_set_raw_mode();
    this->ncurses_set_cursor();
}

void Terminal::uninitialize()
{
    if (!is_initialized_)
        return;
    ::wrefresh(::stdscr);
    is_initialized_ = false;
    ::endwin();
}

// getmaxx/getmaxy are non-standard.
auto Terminal::width() const -> std::size_t
{
    auto x = 0;
    if (auto y = 0; is_initialized_)
        getmaxyx(::stdscr, y, x);
    return x;
}

auto Terminal::height() const -> std::size_t
{
    auto y = 0;
    if (auto x = 0; is_initialized_)
        getmaxyx(::stdscr, y, x);
    return y;
}

void Terminal::set_refresh_rate(std::chrono::milliseconds duration)
{
    refresh_rate_ = duration;
    if (is_initialized_)
        ::timeout(refresh_rate_.count());
}

void Terminal::set_background(Glyph const& tile)
{
    background_ = tile;
    if (is_initialized_)
        this->repaint_all();
}

void Terminal::set_palette(Color_palette const& colors)
{
    if (!is_initialized_ or !this->has_color())
        return;
    // dynamic_color_engine.clear(); // TODO
    palette_ = colors;
    for (auto const& def : colors) {
        std::visit(
            [&](auto const& d) {
                this->set_color_definition(def.color, def.ansi, d);
            },
            def.value);
    }
    this->repaint_all();
    palette_changed(palette_);
}

void Terminal::initialize_pairs(Color c, ANSI a)
{
    for (auto const& def : palette_) {
        ::init_pair(this->color_index(c, def.color), a.value, def.ansi.value);
        ::init_pair(this->color_index(def.color, c), def.ansi.value, a.value);
    }
}

void Terminal::set_color_definition(Color c, ANSI a, std::monostate)
{
    this->initialize_pairs(c, a);
}

void Terminal::set_color_definition(Color c, ANSI a, True_color value)
{
    this->initialize_pairs(c, a);
    this->term_set_color(a, value);
}

void Terminal::set_color_definition(Color c, ANSI a, Dynamic_color value)
{
    this->initialize_pairs(c, a);
    // dynamic_color_engine.register(a, value); // makes calls to term_set_color
}

void Terminal::show_cursor(bool show)
{
    show_cursor_ = show;
    if (is_initialized_)
        this->ncurses_set_cursor();
}

void Terminal::raw_mode(bool enable)
{
    raw_mode_ = enable;
    if (is_initialized_)
        this->ncurses_set_raw_mode();
}

auto Terminal::has_color() const -> bool
{
    if (is_initialized_)
        return ::has_colors() == TRUE;
    return false;
}

auto Terminal::has_extended_colors() const -> bool
{
    if (is_initialized_)
        return COLORS >= 16;
    return false;
}

auto Terminal::color_count() const -> short
{
    if (is_initialized_)
        return COLORS;
    return 0;
}

auto Terminal::can_change_colors() const -> bool
{
    if (is_initialized_)
        return ::can_change_color() == TRUE;
    return false;
}

auto Terminal::color_pair_count() const -> int
{
    if (is_initialized_)
        return COLOR_PAIRS;
    return 0;
}

auto Terminal::color_index(Color fg, Color bg) const -> short
{
    short const color_n = this->get_palette_color_count();
    short const offset  = 1;
    short const fg_mod  = fg.value % color_n;
    short const bg_mod  = bg.value % color_n;
    return offset + fg_mod * color_n + bg_mod;
}

void Terminal::term_set_color(ANSI a, True_color value)
{
    if (!this->can_change_colors())
        throw Terminal_error{"Terminal cannot re-define color values."};

    ::init_color(a.value, scale(value.red()), scale(value.green()),
                 scale(value.blue()));
}

void Terminal::ncurses_set_raw_mode() const
{
    if (raw_mode_) {
        ::nocbreak();
        ::raw();
    }
    else {
        ::noraw();
        ::cbreak();
    }
}

void Terminal::ncurses_set_cursor() const
{
    show_cursor_ ? ::curs_set(1) : ::curs_set(0);
}

void Terminal::repaint_all()
{
    auto* const head = System::head();
    if (head == nullptr)
        return;
    for (auto* const d : head->get_descendants())
        d->update();
}

}  // namespace cppurses
