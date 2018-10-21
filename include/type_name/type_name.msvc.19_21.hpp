#ifndef ADAM_BADURA_TYPE_NAME_TYPE_NAME_MSVC_19_21_HPP
#define ADAM_BADURA_TYPE_NAME_TYPE_NAME_MSVC_19_21_HPP

#include <string_view>

template<typename T>
struct type_name
{
private:
	static constexpr auto get() noexcept
	{
		constexpr std::string_view full_name{ __FUNCSIG__ };
		constexpr std::string_view left_marker{ "type_name<" };
		constexpr std::string_view right_marker{ ">::get(" };

		constexpr auto left_marker_index = full_name.find(left_marker);
		static_assert(left_marker_index != std::string_view::npos);
		constexpr auto start_index = left_marker_index + left_marker.size();
		constexpr auto end_index = full_name.find(right_marker, left_marker_index);
		static_assert(end_index != std::string_view::npos);
		constexpr auto length = end_index - start_index;

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
