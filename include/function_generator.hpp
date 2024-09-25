#pragma once
#include <string>
#include <vector>
#include <iostream>

#include "utils.hpp"

namespace FunctionGenerator {

struct ParseData {
	std::vector<std::string> types;
	std::vector<std::vector<std::string>> init_values;
	std::vector<std::string> var_names;
	std::vector<std::string> expressions;
};

template<typename StringType>
using InitialValueTokens = std::vector<StringType>;

template<typename StringType>
std::ostream& GenerateTestCaseBlock(
		std::ostream& out, std::string_view type,
		const std::vector<StringType>& init_values,
		const std::vector<StringType>& var_names,
		const std::vector<StringType>& expressions,
		int indentation_level ) {

	using namespace std;
	using namespace Utils::String;

	out	<< GetIndentation(indentation_level) << "{" << endl;

	++indentation_level;

	// Задает переменные
	for (size_t i = 0; i < var_names.size() && i < init_values.size(); i++) {
		out	<< GetIndentation(indentation_level)
			<< type << " " << var_names.at(i) << " = "
			<< init_values.at(i) << ";" << endl;
	}

	// Выводит выражения
	for (const StringType& expr : expressions) {
		out	<< GetIndentation(indentation_level)
			<< "std::cout <<" << " \"" << expr << " = \" << "
			<< expr << " << std::endl;" << endl;
	}

	--indentation_level;

	out << GetIndentation(indentation_level) << "}" << endl;

	return out;
}

template<typename StringType> void GenerateTestFunction(
		std::ostream& out, std::string_view function_name,
		const std::vector<StringType>& types,
		const std::vector<std::vector<StringType>>& initial_values,
		const std::vector<StringType>& var_names,
		const std::vector<StringType>& expressions) {

	using namespace std;
	out 	<< "void " << function_name << "() {" << endl;

	for (size_t i = 0; i < types.size() && i < initial_values.size(); i++) {
		GenerateTestCaseBlock(out, types.at(i),
				initial_values.at(i),
				var_names, expressions, 1) << endl;
	}

	out << "}" << endl;
}

ParseData ParseInstructions(std::istream& in);

} // namespace FunctionGenerator