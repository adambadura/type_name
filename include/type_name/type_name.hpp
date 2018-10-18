#ifndef ADAM_BADURA_TYPE_NAME_TYPE_NAME_HPP
#define ADAM_BADURA_TYPE_NAME_TYPE_NAME_HPP

#if defined(__GNUC__)
#	if (__GNUC__ > 7) || (__GNUC__ == 7 && __GNUC_MINOR__ >= 3)
#		include "type_name.gcc.7.3.hpp"
#	else
#		error When using GCC, at least version 7.3 is required.
#	endif
#else
#	error Unsupported compiler.
#endif

#endif
