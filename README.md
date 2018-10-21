# type_name

A C++17-compatible, compile-time type name retrieval library.

## Usage

Include `type_name.hpp` (with adviced approach, see [instructions below](#Building_and_installing), do it with `<type_name/type_name.hpp>`) and then use `type_name` meta-function and corresponding `type_name_v` helper variable template much the same as with meta-functions from standard `<type_traits>`. `type_name` takes a single type argument and it's value is of `std::string_view` type.

### Examples

```c++
#include <type_name/type_name.hpp>
#include <string>
#include <utility>
#include <vector>

static_assert(type_name_v<bool> == "bool");
static_assert(type_name_v<int> == "int");
static_assert(type_name_v<std::string> == "std::__cxx11::basic_string<char>");
static_assert(type_name_v<std::vector<std::pair<std::string, double>>> == "std::vector<std::pair<std::__cxx11::basic_string<char>, double> >");
static_assert(type_name_v<decltype(0.1 * 10)> == "double");
static_assert(type_name_v<type_name<type_name<type_name<bool>>>> == "type_name<type_name<type_name<bool> > >");
```

`type_name` can also be used in member methods to get the type of the class:

```c++
template<typename T, int N>
struct type
{
	void foo() const
	{
		std::cout << type_name_v<decltype(*this)> << '\n';
	}
};

type<int, 10>{}.foo();
// Will output: const type<int, 10>&
```

Keep in mind however that `type_name`:
* Provides static type. If `foo` in the example would be `virtual` and called by a derived class, it would still output the same, rather than derived type name.
* Includes `const` for `const` methods and `&` or `&&` ref-qualifier of the method.
* **Most importantly, keep in mind that the actual name of the type is compiler dependent!**

## Implementation

Implementation relies on `__PRETTY_FUNCTION__` compiler extension provided by GCC and clang. The symbol is old, however for the code to compile correctly, GCC must be at version 7.3 at least while clang at version 5 at least. Visual C++ provides `__FUNCSIG__` which is similar enough for the same "algorithm" to work with minor changes, with the requirement of the version to be at least 19.21 (some versions prior to 19.21 might work as well, not all of them were checked).

Note that even though the `__PRETTY_FUNCTION__` (and `__FUNCSIG__`) look like preprocessor symbols, they are not! The information they provide is not available at preprocessing phase and a file containing those symbols will still have them after being preprocessed.

Note also that standard-specified `__func__` cannot be used for this purpose:
* In general - because it is not specified what exactly it contains.
* In specific case here - because GCC, clang and Visual C++ provide there only the function name (not really surprising...) skipping arguments (template or not).

The unpleasant consequence of this approach is that the library is compiler-dependent. Even within the GCC itself, it is still dependent on the current version and manual checks of what `__PRETTY_FUNCTION__` actually contains since it is not specified by GCC (see [6.48 Function Names as Strings](https://gcc.gnu.org/onlinedocs/gcc/Function-Names.html)).

## CMake support

The library provides CMake support, based mostly on articles:
* [It's Time To Do CMake Right](https://pabloariasal.github.io/2018/02/19/its-time-to-do-cmake-right/) by Pablo Arias and
* [Creating a Header-Only Library with CMake](http://mariobadr.com/creating-a-header-only-library-with-cmake.html) by Mario Badr.

However, since the library consists of only a few header files it is very easy to use it with any build system or without a build system at all.

## Building and installing

### With CMake

First, build and install the library. You can do it for example with following commands (executed from the root of the library clone):

```
cmake -E make_directory build
cmake -E chdir build cmake [-G "<generator>"] ["-DCMAKE_INSTALL_PREFIX=<path>"] ../
cmake -E chdir build cmake --build . --target install
cmake -E remove_directory build
```

where you can optionally provide the following:
* `<generator>` - the generator used by CMake to generate actual build system.
* `<path>` - the path under which the library will be installed. If you provide one, use that path later when referring to the library from your project. If the path is relative, keep in mind that it will be relative to the `build/` subdirectory.

Note that there are more options to CMake. This lists only two basic ones, that are later needed to use the library.

### Without CMake

Copy the library wherever you want.

## Linking with the library

### With CMake

Add following to your `CMakeLists.txt`:
```cmake
find_package(TypeName 1.0 REQUIRED)
```

Then link to the library by doing the following:
```cmake
target_link_libraries(<your_target> AdamBadura::TypeName)
```

Keep in mind that if you have used a non-default installation directory while building and installing (the `CMAKE_INSTALL_PREFIX`), then CMake probably will not be able to locate the library by itself. You will have to help by providing the `<path>/lib/cmake/type_name/` as either `TypeName_DIR` variable or by appending it to the `CMAKE_PREFIX_PATH` list. Both can be done for example using the `"-D<var>=<value>"` argument on a `cmake` call when configuring your project.

### Without CMake

Ensure that the `include/type_name/type_name.hpp` file is on your include path. Or even better, have the `include/` directory on your include path instead and then include the header using `<type_name/type_name.hpp>`.

## Future development

1. **Introspection of the value.** For example skipping or iterating over namespaces, counting template arguments, extracting template arguments, ...
2. **Support for older compilers.** It seems that older compilers and older standards could still deliver the same value as a fixed size character array. However, it would require significantly more code. Probably use of support library for compile-time strings handling.
3. **Enum value name query.** It seems this could be used to provide a meta-function to query enum value as a string. The main difficulty is that there is no auto-deduction for template type arguments which means that providing enum value alone is not enough and one must get first the enum type and then the value.
