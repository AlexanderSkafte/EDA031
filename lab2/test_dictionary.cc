
#include <iostream>
#include "dictionary.h"

int main()
{
	using namespace std;

	Dictionary dict;

	if (!dict.contains("hand")) {
		cout << "Fail: common word." << endl;
		return 1;
	}

	if (dict.contains("asdlkjalusd")) {
		cout << "Fail: random noise string." << endl;
		return 1;
	}

	if (dict.contains("")) {
		cout << "Fail: empty string." << endl;
		return 1;
	}

	cout << "Passed all tests successfully." << endl;
}

