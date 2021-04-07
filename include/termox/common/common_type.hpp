#ifndef CATERM_COMMON_COMMON_TYPE_HPP
#define CATERM_COMMON_COMMON_TYPE_HPP
#include <type_traits>

#include <caterm/widget/widget.hpp>

namespace ox {

/// If T and U are the same type, then return T, else return ox::Widget.
/** Useful in layout wrappers to provide a bit of convinience. */
template <typename T, typename U>
using Common_type = std::conditional_t<std::is_same_v<T, U>, T, ox::Widget>;

}  // namespace ox
#endif  // CATERM_COMMON_COMMON_TYPE_HPP
