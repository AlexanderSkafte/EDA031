
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "date.h"

using namespace std;

template <typename T>
T string_cast(const string& s)
{
	T object;
	istringstream iss(s);
	if (iss >> object) {
		return object;
	} else {
		throw invalid_argument("Cannot cast string to object.");
	}
}

int main()
{
	try {
		int i = string_cast<int>("123");
		double d = string_cast<double>("12.34");
		Date date = string_cast<Date>("2015-01-10");
		cout << i << endl;
		cout << d << endl;
		cout << date << endl;
	} catch (std::invalid_argument& e) {
		cout << "Error: " << e.what() << endl;
	}
}

