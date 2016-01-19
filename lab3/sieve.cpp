
#include <iostream>
#include <string>
#include <vector>

#define DEBUG(X) // Not debugging
//#define DEBUG(X) X // Debugging

using namespace std;

const char PRIME     = 'P';
const char COMPOSITE = 'C';

void mark(string& s, const unsigned int m)
{
	s[m] = COMPOSITE;
}

string sieve(const unsigned int M)
{
	string s(M, PRIME);
	DEBUG(cout << s << endl);
	mark(s, 0);
	mark(s, 1);
	for (unsigned int i = 2; i <= M; ++i) {
		if (s[i] == PRIME) {
			DEBUG(cout << "Found prime " << i << ", mark ");
			for (unsigned int j = i; i + j <= M; j += i) {
				DEBUG(cout << (i + j) << " ");
				mark(s, (i + j));
			}
			DEBUG(cout << endl);
		}
	}
	DEBUG(cout << s << endl);
	return s;
}

vector<int> primes(const string& s)
{
	vector<int> v;
	for (unsigned int i = 0; i <= s.length(); ++i) {
		if (s[i] == PRIME) {
			v.push_back(i);
		}
	}
	return v;
}

size_t largest_below(const unsigned int m)
{
	return sieve(m).rfind(PRIME);
}

int main(int argc, char* argv[])
{
	if (argc != 2) {
		cout << "usage: sieve <number>" << endl;
		return 1;
	}

	unsigned int	M = stoi(argv[1]) + 1;
	string s = sieve(M);
	cout << s << endl;

	cout << "Primes:";
	for (int p : primes(s)) {
		cout << " " << p;
	}
	cout << endl;

	cout << "Largest below 100000: " << largest_below(100000) << endl;
}

