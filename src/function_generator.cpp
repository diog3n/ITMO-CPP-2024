#include "function_generator.hpp"
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;

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

const string NO_EXPRESSIONS_MSG = "No expressions given";

const string NO_VAR_NAMES_MSG = "No variable names were given";

const string NO_TYPES_GIVEN_MSG = "No type names were given";

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

	if (parse_data.expressions.empty())
		throw invalid_argument(
			MakeExceptionString(line_counter,
					NO_EXPRESSIONS_MSG));

	if (parse_data.types.empty())
		throw invalid_argument(
			MakeExceptionString(line_counter,
					NO_TYPES_GIVEN_MSG));

	if (parse_data.var_names.empty())
		throw invalid_argument(
			MakeExceptionString(line_counter,
					NO_VAR_NAMES_MSG));

	return parse_data;
}
