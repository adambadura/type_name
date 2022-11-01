#ifndef ADAM_BADURA_TYPE_NAME_TYPE_NAME_GCC_7_3_HPP
#define ADAM_BADURA_TYPE_NAME_TYPE_NAME_GCC_7_3_HPP

#include <cassert>
#include <string_view>

template<typename T>
struct type_name
{
private:
	static constexpr auto get() noexcept
	{
		const std::string_view full_name{ __PRETTY_FUNCTION__ };
		const std::string_view left_marker{ "[with T = " };
		const std::string_view right_marker{ "]" };

		const auto left_marker_index = full_name.find(left_marker);
		assert(left_marker_index != std::string_view::npos);
		const auto start_index = left_marker_index + left_marker.size();
		const auto end_index = full_name.find(right_marker, left_marker_index);
		assert(end_index != std::string_view::npos);
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

#endif
