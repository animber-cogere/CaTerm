[![Build Status](https://github.com/animber-coder/CaTerm/workflows/build/badge.svg)](https://github.com/animber-coder/CaTerm/actions?query=workflow%3Abuild)
[![Read the Manual](https://img.shields.io/badge/-Manual-yellow.svg)](docs/manual/index.md)
[![Read the Reference](https://img.shields.io/badge/-API%20Reference-blue.svg)](https://animber-coder.github.io/CaTerm/hierarchy.html)

# CaTerm 🐂

**CaTerm** is a Terminal User Interface Framework for C++17. Built on top of
[Escape](https://github.com/animber-coder/Escape), it defines a set of Widgets,
Layouts, and Events that make it quick to craft unique user interfaces in the
terminal.

<!-- TODO - single gif of multiple demos -->
<p align="center">
  <img src="docs/images/caterm-demos.gif">
</p>

The [Widget Library](docs/manual/widget.md#widget-library) contains many common
Widget and Layout types that can be pieced together to create a composite
interface. It's easy to expand on top of these types to create new Widgets and
Layouts.

This project was previously named **CPPurses**.

## Usage

<!-- TODO this is only one usage, and it isn't the common one, its misleading. -->

```cpp
#include <caterm/caterm.hpp>

int main()
{
    using namespace ox;
    auto app =
        layout::vertical(
            textbox("Hello, World!" | fg(Color::Red) | Trait::Bold) | pipe::name("tb"),
            layout::horizontal<Button>(
                button("Button 1") | bg(Color::Blue) | pipe::name("b1"),
                button("Button 2") | bg(Color::Violet) | pipe::name("b2")
            ) | pipe::fixed_height(1)
        );
    auto& tb = app->find_child_by_name("tb");
    app->find_child_by_name("b1") | pipe::on_press([&tb]{ tb.append("Button 1 Pressed"); });
    app->find_child_by_name("b2") | pipe::on_press([&tb]{ tb.append("Button 2 Pressed"); });
    return System{}.run(*app);
}
```

<!-- TODO Make this an animated gif -->
<p align="center">
  <img src="docs/images/example_1.png">
</p>

See the [Manual](docs/manual/index.md) for more in depth explanations and
examples.

Reference documentation can be found
[here](https://animber-coder.github.io/CaTerm/hierarchy.html).

## Features

- Event System to handle Mouse, Keyboard and Animation events, among others

- Signals and Slots to communicate between Widgets

- Color Palettes and Dynamic Colors

- Animation

- Inherit from existing Widgets and Layouts to create new UI elements

- Library of commonly used Widgets and Layouts

## Build Instructions

CaTerm depends on a Signals library and nCurses, these are both included as
git submodules.

```
git clone https://github.com/animber-coder/CaTerm.git
mkdir CaTerm/build && cd CaTerm/build
git submodule update --init               # Pull in dependencies
cmake .. -DCMAKE_BUILD_TYPE=Release       # Generate Makefiles
make                                      # Build library
make demos                                # Build demos(optional)
make caterm.unit.tests                    # Build Unit Tests(optional)
make caterm.ui.tests                      # Build UI Tests(optional)
```

## Using the Library

It is recommended to clone this library into your project and use it as a
submodule rather than installing it to your system. This way you can lock your
application to a specific version of CaTerm.

CMake will add the library target `CaTerm` if you add the CaTerm directory
with `add_subdirectory(...)`.

```cmake
# CMakeLists.txt
cmake_minimum_required(VERSION 3.2)
add_executable(my_app
               my_app.main.cpp
               ...
)

# CaTerm is cloned into a directory named external/
add_subdirectory(external/CaTerm)
target_link_libraries(foo CaTerm)
```

## License
This software is distributed under the [MIT License](LICENSE.txt).
