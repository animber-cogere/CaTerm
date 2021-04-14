#ifndef CATERM_WIDGET_WIDGETS_LINE_HPP
#define CATERM_WIDGET_WIDGETS_LINE_HPP
#include <memory>

#include <caterm/widget/layouts/horizontal.hpp>
#include <caterm/widget/layouts/vertical.hpp>
#include <caterm/widget/pipe.hpp>
#include <caterm/widget/widget.hpp>

namespace ox {

/// A Vertical or Horizontal single width line divider.
template <template <typename> typename Layout_t>
class Line : public Widget {
   public:
    struct Parameters {};

   public:
    Line()
    {
        if constexpr (is_vertical)
            *this | pipe::fixed_width(1) | pipe::wallpaper(U'│');
        else
            *this | pipe::fixed_height(1) | pipe::wallpaper(U'─');
    }

    Line(Parameters) : Line{} {}

   private:
    static auto constexpr is_vertical = layout::is_vertical_v<Layout_t<Widget>>;
};

/// Create an instance of a Line.
template <template <typename> typename Layout_t>
[[nodiscard]] auto line() -> std::unique_ptr<Line<Layout_t>>
{
    return std::make_unique<Line<Layout_t>>();
}

/// Create an instance of a Line.
template <template <typename> typename Layout_t>
[[nodiscard]] auto line(typename Line<Layout_t>::Parameters p)
    -> std::unique_ptr<Line<Layout_t>>
{
    return std::make_unique<Line<Layout_t>>(std::move(p));
}

using VLine = Line<layout::Vertical>;

/// Create an instance of a VLine.
[[nodiscard]] inline auto vline() -> std::unique_ptr<VLine>
{
    return std::make_unique<VLine>();
}

/// Create an instance of a VLine.
[[nodiscard]] inline auto vline(typename VLine::Parameters p)
    -> std::unique_ptr<VLine>
{
    return std::make_unique<VLine>(std::move(p));
}

using HLine = Line<layout::Horizontal>;

/// Create an instance of an HLine.
[[nodiscard]] inline auto hline() -> std::unique_ptr<HLine>
{
    return std::make_unique<HLine>();
}

/// Create an instance of an HLine.
[[nodiscard]] inline auto hline(typename HLine::Parameters p)
    -> std::unique_ptr<HLine>
{
    return std::make_unique<HLine>(std::move(p));
}

}  // namespace ox
#endif  // CATERM_WIDGET_WIDGETS_LINE_HPP
