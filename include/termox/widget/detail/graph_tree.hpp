#ifndef CATERM_WIDGET_DETAIL_GRAPH_TREE_HPP
#define CATERM_WIDGET_DETAIL_GRAPH_TREE_HPP
#include <string>

namespace ox {
class Widget;
}  // namespace ox

namespace ox::detail {

/// Outputs filename.gz graph description of widget tree hierarchy.
void graph_tree(Widget const& w, std::string const& filename);

}  // namespace ox::detail
#endif  // CATERM_WIDGET_DETAIL_GRAPH_TREE_HPP
