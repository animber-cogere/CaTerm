#ifndef CATERM_TERMINAL_TERMINAL_ERROR_HPP
#define CATERM_TERMINAL_TERMINAL_ERROR_HPP
#include <stdexcept>

namespace ox {

/// Runtime Terminal Error
/** Used when a terminal does not support some feature. */
struct Terminal_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

}  // namespace ox
#endif  // CATERM_TERMINAL_TERMINAL_ERROR_HPP
