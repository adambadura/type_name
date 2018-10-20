#ifndef ADAM_BADURA_TYPE_NAME_TYPE_NAME_CLANG_HPP
#define ADAM_BADURA_TYPE_NAME_TYPE_NAME_CLANG_HPP

#if (__clang_major__ >= 5)
#	include "type_name.clang.5.hpp"
#else
#	error When using clang, at least version 5 is required.
#endif

#endif
