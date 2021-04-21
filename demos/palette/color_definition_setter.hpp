#ifndef CATERM_DEMOS_PALETTE_COLOR_DEFINITION_SETTER_HPP
#define CATERM_DEMOS_PALETTE_COLOR_DEFINITION_SETTER_HPP
#include <cctype>
#include <string>

#include <caterm/painter/color.hpp>
#include <caterm/painter/painter.hpp>
#include <caterm/widget/layouts/vertical.hpp>
#include <caterm/widget/widgets/confirm_button.hpp>
#include <caterm/widget/widgets/text_view.hpp>
#include <caterm/widget/widgets/textline.hpp>

#include "color_control.hpp"
#include "color_display.hpp"
#include "export_panel.hpp"

namespace palette {

/// Provides interface and implementation of setting a specific color value.
class Color_definition_setter : public ox::layout::Vertical<> {
    ox::Color current_color_{ox::Color::White};

    Color_display& color_display_{
        this->make_child<Color_display>(current_color_)};

    Color_control& color_control_{this->make_child<Color_control>()};

    Export_panel& export_panel_{this->make_child<Export_panel>()};

   public:
    Color_definition_setter();

    /// Change the color you are setting the definition of.
    void change_current_color(ox::Color color);

    /// Return the color you are setting the definition of.
    auto current_color() const -> ox::Color { return current_color_; }
};

}  // namespace palette
#endif  // CATERM_DEMOS_PALETTE_COLOR_DEFINITION_SETTER_HPP
