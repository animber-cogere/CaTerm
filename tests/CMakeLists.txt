cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

# Checkbox
add_executable(checkbox EXCLUDE_FROM_ALL checkbox.test.cpp)
target_link_libraries(checkbox PRIVATE CaTerm)

add_custom_target(
    caterm-tests
    DEPENDS
        checkbox
)
