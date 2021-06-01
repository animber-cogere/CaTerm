#ifndef CATERM_DEMOS_GAME_OF_LIFE_GOL_DEMO_HPP
#define CATERM_DEMOS_GAME_OF_LIFE_GOL_DEMO_HPP
#include <caterm/terminal/terminal.hpp>
#include <caterm/widget/layouts/horizontal.hpp>
#include <caterm/widget/widgets/accordion.hpp>

#include "colors.hpp"
#include "gol_widget.hpp"
#include "pattern_store.hpp"
#include "rule_store.hpp"
#include "side_panel.hpp"

namespace gol {

class GoL_demo : public ox::layout::Horizontal<> {
   public:
    GoL_demo();

   public:
    using Side_panel_accordion =
        ox::HAccordion<Side_panel, ox::Bar_position::Last>;

   public:
    Side_panel_accordion& side_panel_accordion =
        this->make_child<Side_panel_accordion>(
            {U"Settings", ox::Align::Center, U'│' | fg(color::Light_green)});
    Side_panel& side_panel  = side_panel_accordion.wrapped();
    GoL_widget& gol_display = this->make_child<GoL_widget>();

   private:
    Rule_store rule_store_;
    Pattern_store pattern_store_;

   private:
    void add_rule_example(Rule_store::Name name, std::string_view rule_string)
    {
        rule_store_.add_rule(name, parse_rule_string(rule_string));
        side_panel.patterns_rulesets.rulesets.add_option(std::u32string{name});
    }

    void add_pattern_example(Pattern_store::Name name, Pattern pattern)
    {
        pattern_store_.add_pattern(name, pattern);
        side_panel.patterns_rulesets.patterns.add_option(std::u32string{name});
    }
};

}  // namespace gol
#endif  // CATERM_DEMOS_GAME_OF_LIFE_GOL_DEMO_HPP
