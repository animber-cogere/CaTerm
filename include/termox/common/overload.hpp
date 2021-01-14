#ifndef CATERM_COMMON_OVERLOAD_HPP
#define CATERM_COMMON_OVERLOAD_HPP
namespace ox {

/// Overload pattern for function objects.
/** Construct with multiple function objects to get a single object with
 *  overloaded operator() from each function object given. */
template <typename... Ts>
struct Overload : Ts... {
    using Ts::operator()...;
};

template <typename... Ts>
Overload(Ts...) -> Overload<Ts...>;

}  // namespace ox
#endif  // CATERM_COMMON_OVERLOAD_HPP
