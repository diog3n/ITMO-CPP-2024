#include "utils.hpp"
#include <stdexcept>

std::string_view Utils::View::Trim(std::string_view view, char to_trim) {
	size_t start = view.find_first_not_of(to_trim);

	if (start == std::string_view::npos)
		return "";

	size_t end = view.find_last_not_of(to_trim);

	return Subview(view, start, end + 1);
}

std::string_view
Utils::View::Subview(std::string_view view, size_t start, size_t end) {
	if (start > end)
		throw std::invalid_argument("Subview's start is "
				"bigger than end");
	return view.substr(start, end - start);
}

std::vector<std::string_view>
Utils::View::SplitBy(std::string_view line, char by, bool trim_spaces) {
	std::vector<std::string_view> result;
	size_t start = 0;
	size_t end = line.find(by, start);

	while (end != std::string_view::npos) {
		if (trim_spaces) {
			result.emplace_back(
					Trim(Subview(line, start, end), ' '));
		} else {
			result.emplace_back(Subview(line, start, end));
		}

		start = end + 1;
		end = line.find(by, start);
	}

	if (trim_spaces) {
		result.emplace_back(Trim(
			Subview(line, start, std::string_view::npos), ' '));
	} else {
		result.emplace_back(
			Subview(line, start, std::string_view::npos));
	}
	return result;
}

std::string Utils::String::GetIndentation(int level) {
	return std::string(level, '\t');
}