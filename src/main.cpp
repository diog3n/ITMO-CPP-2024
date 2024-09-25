#include "utils.hpp"
#include "function_generator.hpp"
#include <cerrno>
#include <fstream>
#include <iostream>

int GenerateComplexTestFunctionMain(int argc, char **argv) {
	using namespace std;
	using namespace Utils::View;
	using namespace FunctionGenerator;

	ofstream fout(argv[1]);
	ifstream fin(argv[2]);

	if (!fin) {
		cerr	<< "No such file: " << argv[2] << endl;
		return ENOENT;
	}

	ParseData pd = ParseInstructions(fin);

	fout << "#include <iostream>" << endl;
	fout << endl;

	GenerateComplexTestFunction(fout, "TestFunction",
			pd.types,
			pd.init_values,
			pd.var_names,
			pd.expressions);

	return 0;
}

int GenerateSimpleTestFunctionMain(int argc, char **argv) {
	using namespace std;
	using namespace Utils::View;

	ofstream fout(argv[1]);

	string in_types_line;
	cout	<< "Variable types (ex. \"int, unsigned double\"): ";
	getline(cin, in_types_line);

	vector<string_view> type_tokens = SplitBy(in_types_line, ',',
			TRIM_SPACES);

	string in_values_line;
	cout	<< "Pairs of initial values (ex. \"1 2, 4.0 2.1\"): ";
	getline(cin, in_values_line);

	vector<string_view>
	values_tokens_unpaired = SplitBy(in_values_line, ',',
			TRIM_SPACES);

	vector<FunctionGenerator::InitialValueTokens> values_tokens;

	for (string_view value_pair : values_tokens_unpaired) {
		vector<string_view>
		pair_vector = SplitBy(value_pair, ' ', TRIM_SPACES);

		values_tokens.emplace_back(pair_vector.at(0),
				pair_vector.at(1));
	}

	if (values_tokens.size() != type_tokens.size()) {
		cerr 	<< "One type should have exactly one pair of "
			<< "initial values." << endl;
	}

	fout << "#include <iostream>" << endl;
	fout << endl;

	FunctionGenerator::GenerateSimpleTestFunction(fout, "TestFunction",
			type_tokens, values_tokens);

	return 0;
}

int main(int argc, char **argv) {
	using namespace std;
	using namespace Utils::View;

	if (argc < 2) {
		cout	<< "Usage: funcgen [out_file]" << endl;
		cout	<< "Or: funcgen [out_file] [instructions_file]" << endl;
		return EINVAL;
	}

	if (argc == 2)
		return GenerateSimpleTestFunctionMain(argc, argv);

	if (argc == 3)
		return GenerateComplexTestFunctionMain(argc, argv);
}