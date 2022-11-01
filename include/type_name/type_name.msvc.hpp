#ifndef ADAM_BADURA_TYPE_NAME_TYPE_NAME_MSVC_HPP
#define ADAM_BADURA_TYPE_NAME_TYPE_NAME_MSVC_HPP

#if (_MSC_VER >= 1921)
#	include "type_name.msvc.19.21.hpp"
#else
#	error When using Microsoft (R) C/C++ Optimizing Compiler, at least version 19.21 is required.
#endif

#endif
