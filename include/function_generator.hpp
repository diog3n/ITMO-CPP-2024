#pragma once
#include <string>
#include <vector>

namespace FunctionGenerator {

using InitialValueTokens = std::pair<std::string_view, std::string_view>;

extern const std::vector<std::string> arithmetic_operations;

void GenerateSimpleTestFunction(std::ostream& out, const std::string& function_name,
		const std::vector<std::string_view>& types,
		const std::vector<InitialValueTokens>& initial_values);

void GenerateComplexTestFunction(std::ostream& out,
		const std::string& function_name,
		const std::vector<std::string>& types,
		const std::vector<std::vector<std::string>>& initial_values,
		const std::vector<std::string> var_names,
		const std::vector<std::string> expressions);

struct ParseData {
	std::vector<std::string> types;
	std::vector<std::vector<std::string>> init_values;
	std::vector<std::string> var_names;
	std::vector<std::string> expressions;
};

ParseData ParseInstructions(std::istream& in);

} // namespace FunctionGenerator