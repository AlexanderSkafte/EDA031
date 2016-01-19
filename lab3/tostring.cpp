
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

template <typename T>
string toString(T object)
{
	ostringstream oss;
	oss << object;
	return oss.str();
}

int main()
{
	bool success = true;

	int		i = 1337;
	double	d = 2.72;

	if (toString(i) != "1337") {
		cout << "toString of int failed." << endl;
		success = false;
	}
	if (toString(d) != "2.72") {
		cout << "toString of double failed." << endl;
		success = false;
	}

	if (success) {
		cout << "Passed all tests successfully." << endl;
	}
}

