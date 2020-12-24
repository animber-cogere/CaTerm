#ifndef CATERM_HPP
#define CATERM_HPP

#include <caterm/painter/brush.hpp>
#include <caterm/painter/color.hpp>
#include <caterm/painter/glyph.hpp>
#include <caterm/painter/glyph_matrix.hpp>
#include <caterm/painter/glyph_string.hpp>
#include <caterm/painter/painter.hpp>
#include <caterm/painter/trait.hpp>
#include <caterm/painter/utility/wchar_to_bytes.hpp>

#include <caterm/system/key.hpp>
#include <caterm/system/mouse.hpp>

#include <caterm/system/animation_engine.hpp>
#include <caterm/system/event_loop.hpp>
#include <caterm/system/shortcuts.hpp>
#include <caterm/system/system.hpp>

#include <caterm/terminal/input.hpp>
#include <caterm/terminal/output.hpp>
#include <caterm/terminal/terminal.hpp>

#include <caterm/widget/layouts/horizontal.hpp>
#include <caterm/widget/layouts/stack.hpp>
#include <caterm/widget/layouts/vertical.hpp>

#include <caterm/widget/widgets/button.hpp>
#include <caterm/widget/widgets/checkbox.hpp>
#include <caterm/widget/widgets/color_select.hpp>
#include <caterm/widget/widgets/confirm_button.hpp>
#include <caterm/widget/widgets/cycle_box.hpp>
#include <caterm/widget/widgets/cycle_stack.hpp>
#include <caterm/widget/widgets/graph.hpp>
#include <caterm/widget/widgets/label.hpp>
#include <caterm/widget/widgets/line_edit.hpp>
#include <caterm/widget/widgets/log.hpp>
#include <caterm/widget/widgets/matrix_display.hpp>
#include <caterm/widget/widgets/menu.hpp>
#include <caterm/widget/widgets/menu_stack.hpp>
#include <caterm/widget/widgets/number_edit.hpp>
#include <caterm/widget/widgets/open_file.hpp>
#include <caterm/widget/widgets/save_file.hpp>
#include <caterm/widget/widgets/status_bar.hpp>
#include <caterm/widget/widgets/text_display.hpp>
#include <caterm/widget/widgets/textbox.hpp>
#include <caterm/widget/widgets/titlebar.hpp>
#include <caterm/widget/widgets/vertical_slider.hpp>

#include <caterm/widget/area.hpp>
#include <caterm/widget/border.hpp>
#include <caterm/widget/focus_policy.hpp>
#include <caterm/widget/layout.hpp>
#include <caterm/widget/point.hpp>
#include <caterm/widget/size_policy.hpp>
#include <caterm/widget/widget.hpp>
#include <caterm/widget/widget_slots.hpp>

#endif  // CATERM_HPP