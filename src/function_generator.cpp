#include "function_generator.hpp"
#include <sstream>
#include <stdexcept>

using namespace std;

const vector<string> FunctionGenerator::arithmetic_operations = {
	"+", "-", "/", "*",
};

const string
EXPECTED_VAR_MSG = "Expected variable definition after the \"var\" keyword";

const string
EXPECTED_TYPE_MSG = "Expected type definition after the \"type\" keyword";

const string
EXPECTED_EXPR_MSG = "Expected expresssion after the \"expr\" keyword";

const string
SUDDEN_EOF_MSG = "Unexpected end of line";

const string
NOT_ENOUGH_INIT_VALS_MSG = "Amount of initial values must be more or equal "
		"to the amount of declared variable names";

string MakeExceptionString(int line, const string& message) {
	using namespace literals;
	return "line: "s + to_string(line) + ", "s + message;
}

FunctionGenerator::ParseData
FunctionGenerator::ParseInstructions(istream& in) {
	ParseData parse_data;
	string line;
	int line_counter = 1;

	while (getline(in, line)) {
		istringstream iss(line);
		string token;
		iss >> token;

		if (token == "var") {
			if (!(iss >> token)) {
				throw invalid_argument(
					MakeExceptionString(line_counter,
							EXPECTED_VAR_MSG));
			}

			parse_data.var_names.push_back(token);
		} else if (token == "type") {
			bool is_first = true;
			string type;
			iss >> token;

			// Если тип переменной состоит из нескольких слов
			while (token != "=") {
				if (!is_first) {
					type += " ";
				}

				is_first = false;
				type += token;
				if (!(iss >> token))
					break;
			}

			if (type.empty()) {
				throw invalid_argument(
					MakeExceptionString(line_counter,
							EXPECTED_TYPE_MSG));
			}

			vector<string> values;
			while (iss >> token) {
				values.push_back(token);
			}

			if (values.empty()) {
				throw invalid_argument(
					MakeExceptionString(line_counter,
							SUDDEN_EOF_MSG));
			}

			parse_data.types.push_back(type);
			parse_data.init_values.push_back(values);
		} else if (token == "expr") {
			string expr;
			getline(iss, expr);
			if (expr.empty()) {
				throw invalid_argument(
					MakeExceptionString(line_counter,
							EXPECTED_EXPR_MSG));
			}

			parse_data.expressions.emplace_back(expr.begin() + 1,
					expr.end());
		}

		line_counter++;
	}

	for (const vector<string>& inits : parse_data.init_values) {
		if (inits.size() < parse_data.var_names.size())
			throw invalid_argument(
				MakeExceptionString(line_counter,
						NOT_ENOUGH_INIT_VALS_MSG));
	}

	return parse_data;
}

string GetIndentation(int level) {
	return string(level, '\t');
}

ostream& GenerateSimpleTestCaseBlock(
		ostream& out, string_view type,
		const FunctionGenerator::InitialValueTokens& init_values,
		const vector<string>& operations,
		int indentation_level = 0) {

	const string var1_name = "var1";
	const string var2_name = "var2";

	out	<< GetIndentation(indentation_level) << "{" << endl;

	++indentation_level;

	out	<< GetIndentation(indentation_level)
		<< type << " " << var1_name << " = "
		<< init_values.first << ";" << endl;

	out	<< GetIndentation(indentation_level)
		<< type << " " << var2_name << " = "
		<< init_values.second << ";" << endl;

	for (const string& operation : operations) {
		out	<< GetIndentation(indentation_level)
			<< "std::cout << " << var1_name << " "
			<< operation << " " << var2_name << " << std::endl;"
			<< endl;
	}

	--indentation_level;

	out << GetIndentation(indentation_level) << "}";

	return out;
}

void
FunctionGenerator::GenerateSimpleTestFunction(
		ostream& out, const string& function_name,
		const vector<string_view>& types,
		const vector<InitialValueTokens>& initial_values) {
	out 	<< "void " << function_name << "() {" << endl;

	for ( int i = 0; i < types.size() && initial_values.size(); i++) {
		GenerateSimpleTestCaseBlock(out, types.at(i),
				initial_values.at(i),
				arithmetic_operations, 1) << endl;
	}

	out << "}" << endl;
}

ostream& GenerateComplexTestCaseBlock(
		ostream& out, string_view type,
		const vector<string>& init_values,
		const vector<string>& var_names,
		const vector<string>& expressions,
		int indentation_level ) {

	out	<< GetIndentation(indentation_level) << "{" << endl;

	++indentation_level;

	// Задает переменные
	for (size_t i = 0; i < var_names.size() && i < init_values.size(); i++) {
		out	<< GetIndentation(indentation_level)
			<< type << " " << var_names.at(i) << " = "
			<< init_values.at(i) << ";" << endl;
	}

	// Выводит выражения
	for (const std::string& expr : expressions) {
		out	<< GetIndentation(indentation_level)
			<< "std::cout <<" << " \"" << expr << " = \" << "
			<< expr << " << std::endl;" << endl;
	}

	--indentation_level;

	out << GetIndentation(indentation_level) << "}" << endl;

	return out;
}

void FunctionGenerator::GenerateComplexTestFunction(
		ostream& out, const string& function_name,
		const vector<string>& types,
		const vector<vector<string>>& initial_values,
		const vector<string> var_names,
		const vector<string> expressions) {
	out 	<< "void " << function_name << "() {" << endl;

	for (size_t i = 0; i < types.size() && i < initial_values.size(); i++) {
		GenerateComplexTestCaseBlock(out, types.at(i),
				initial_values.at(i),
				var_names, expressions, 1) << endl;
	}

	out << "}" << endl;
}