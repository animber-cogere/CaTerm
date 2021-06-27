#ifndef CATERM_WIDGET_WIDGETS_MATRIX_VIEW_HPP
#define CATERM_WIDGET_WIDGETS_MATRIX_VIEW_HPP
#include <memory>

#include <caterm/painter/glyph_matrix.hpp>
#include <caterm/painter/painter.hpp>
#include <caterm/widget/widget.hpp>

namespace ox {

/// Displays a Glyph_matrix object
class Matrix_view : public Widget {
   public:
    struct Parameters {
        Glyph_matrix matrix;
    };

   public:
    Glyph_matrix matrix;

   public:
    explicit Matrix_view(Glyph_matrix matrix_);

    explicit Matrix_view(Parameters p);

   protected:
    auto paint_event(Painter& p) -> bool override;
};

/// Helper function to create a Matrix_view instance.
[[nodiscard]] auto matrix_view(Glyph_matrix matrix)
    -> std::unique_ptr<Matrix_view>;

/// Helper function to create a Matrix_view instance.
[[nodiscard]] auto matrix_view(Matrix_view::Parameters p)
    -> std::unique_ptr<Matrix_view>;

}  // namespace ox
#endif  // CATERM_WIDGET_WIDGETS_MATRIX_VIEW_HPP
