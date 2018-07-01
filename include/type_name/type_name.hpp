#ifndef ADAM_BADURA_TYPE_NAME_TYPE_NAME_HPP
#define ADAM_BADURA_TYPE_NAME_TYPE_NAME_HPP

#if defined(__GNUC__) && ((__GNUC__ > 7) || (__GNUC__ == 7 && __GNUC_MINOR__ >= 3))

#include <string_view>

template<typename T>
struct type_name
{
private:
	static constexpr auto get() noexcept
	{
		const std::string_view full_name{ __PRETTY_FUNCTION__, sizeof(__PRETTY_FUNCTION__) };
		const std::string_view left_marker{ "[with T = ", 10 };
		const std::string_view right_marker{ "]", 1 };
		const auto start_index = full_name.find(left_marker) + left_marker.size();
		const auto end_index = full_name.find(right_marker, start_index);
		const auto length = end_index - start_index;
		return full_name.substr(start_index, length);
	}

public:
	using value_type = std::string_view;
	static constexpr value_type value{ get() };

	constexpr operator value_type() const noexcept { return value; }
	constexpr value_type operator()() const noexcept { return value; }
};

template<typename T>
inline constexpr auto type_name_v = type_name<T>::value;

#else
#	if defined(__GNUC__)
#		error When using GCC, at least version 7.3 is required.
#	else
#		error Unsupported compiler
#	endif
#endif

#endif
