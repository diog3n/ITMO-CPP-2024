#pragma once
#include <vector>
#include <string_view>

namespace Utils {

namespace View {

constexpr bool TRIM_SPACES		= true;
constexpr bool DO_NOT_TRIM_SPACES 	= false;

std::vector<std::string_view> SplitBy(std::string_view line, char by,
		bool trim_spaces = false);

std::string_view Trim(std::string_view view, char to_trim);

std::string_view Subview(std::string_view view, size_t start, size_t end);

} // namespace View;

} // namespace Utils;