#ifndef ADAM_BADURA_TYPE_NAME_TYPE_NAME_HPP
#define ADAM_BADURA_TYPE_NAME_TYPE_NAME_HPP

#if defined(__clang__)
#	include "type_name.clang.hpp"
#elif defined(__GNUC__)
#	include "type_name.gcc.hpp"
#elif defined(_MSC_VER)
#	include "type_name.msvc.hpp"
#else
#	error Unsupported compiler.
#endif

#endif
