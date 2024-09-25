#include <iostream>

void TestFunction() {
	{
		int var1 = 1;
		int var2 = 2;
		cout << var1 + var2 << endl;
		cout << var1 - var2 << endl;
		cout << var1 / var2 << endl;
		cout << var1 * var2 << endl;
	}
	{
		unsigned double var1 = 0.1;
		unsigned double var2 = 0.2;
		cout << var1 + var2 << endl;
		cout << var1 - var2 << endl;
		cout << var1 / var2 << endl;
		cout << var1 * var2 << endl;
	}
	{
		char var1 = 'a';
		char var2 = 'b';
		cout << var1 + var2 << endl;
		cout << var1 - var2 << endl;
		cout << var1 / var2 << endl;
		cout << var1 * var2 << endl;
	}
}
