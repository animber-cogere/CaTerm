#ifndef CPPURSES_DEMOS_GAME_OF_LIFE_SETTINGS_BOX_HPP
#define CPPURSES_DEMOS_GAME_OF_LIFE_SETTINGS_BOX_HPP
#include <chrono>
#include <string>

#include <signals/signal.hpp>

#include <cppurses/painter/glyph_string.hpp>
#include <cppurses/painter/trait.hpp>
#include <cppurses/widget/layouts/horizontal.hpp>
#include <cppurses/widget/layouts/vertical.hpp>
#include <cppurses/widget/widgets/button.hpp>
#include <cppurses/widget/widgets/checkbox.hpp>
#include <cppurses/widget/widgets/confirm_button.hpp>
#include <cppurses/widget/widgets/label.hpp>
#include <cppurses/widget/widgets/line_edit.hpp>
#include <cppurses/widget/widgets/number_edit.hpp>
#include <cppurses/widget/widgets/toggle_button.hpp>

namespace gol {

struct Clear_step_box : cppurses::layout::Vertical<> {
   public:
    cppurses::Button& step_btn = this->make_child<cppurses::Button>("Step>");

    cppurses::Confirm_button& clear_btn =
        this->make_child<cppurses::Confirm_button>("Clear");

   public:
    Clear_step_box();
};

struct Rule_edit : cppurses::layout::Vertical<> {
   public:
    cppurses::Label& label = this->make_child<cppurses::Label>(
        cppurses::Glyph_string{"Rules[B/S]", cppurses::Trait::Underline});

    cppurses::Line_edit& edit_box =
        this->make_child<cppurses::Line_edit>("3/23");

    sig::Signal<void(const std::string&)> rule_change;

   public:
    Rule_edit();
};

struct Start_pause_btns : cppurses::Toggle_button {
   public:
    sig::Signal<void()>& start_requested = top.pressed;
    sig::Signal<void()>& pause_requested = bottom.pressed;

   public:
    Start_pause_btns();
};

struct Period_box : cppurses::layout::Horizontal<> {
   public:
    cppurses::Labeled_number_edit<unsigned>& value_edit =
        this->make_child<cppurses::Labeled_number_edit<unsigned>>("Period ",
                                                                  120);
    cppurses::Label& units = this->make_child<cppurses::Label>("ms");

    sig::Signal<void(unsigned)>& value_set = value_edit.value_set;

   public:
    Period_box();
};

struct Grid_fade : cppurses::layout::Horizontal<cppurses::Labeled_checkbox> {
   public:
    Child& grid_box = this->make_child("Grid");
    Child& fade_box = this->make_child("Fade");

   public:
    Grid_fade();
};

struct Settings_box : cppurses::layout::Vertical<> {
   public:
    Period_box& period_edit            = this->make_child<Period_box>();
    Start_pause_btns& start_pause_btns = this->make_child<Start_pause_btns>();
    Clear_step_box& clear_step_btns    = this->make_child<Clear_step_box>();
    Grid_fade& grid_fade               = this->make_child<Grid_fade>();
    Rule_edit& rule_edit               = this->make_child<Rule_edit>();

   public:
    sig::Signal<void(const std::string&)>& rule_change = rule_edit.rule_change;
    sig::Signal<void(std::chrono::milliseconds)> period_set;
    sig::Signal<void()>& grid_toggled  = grid_fade.grid_box.toggled;
    sig::Signal<void()>& fade_toggled  = grid_fade.fade_box.toggled;
    sig::Signal<void()>& clear_request = clear_step_btns.clear_btn.pressed;
    sig::Signal<void()>& step_request  = clear_step_btns.step_btn.pressed;

   public:
    Settings_box();
};

}  // namespace gol
#endif  // CPPURSES_DEMOS_GAME_OF_LIFE_SETTINGS_BOX_HPP
