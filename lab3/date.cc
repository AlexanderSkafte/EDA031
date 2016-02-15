#include <ctime>  // time and localtime
#include <iomanip>
#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include "date.h"

using namespace std;

int Date::daysPerMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

Date::Date() {
	time_t timer = time(0);				// time in seconds since 1970-01-01
	tm* locTime = localtime(&timer);	// broken-down time
	year = 1900 + locTime->tm_year;
	month = 1 + locTime->tm_mon;
	day = locTime->tm_mday;
}

Date::Date(int y, int m, int d)
	: year(y)
	, month(m)
	, day(d) {}

int Date::getYear() const {
	return year;
}

int Date::getMonth() const {
	return month;
}

int Date::getDay() const {
	return day;
}

void
Date::setDate(int y, int m, int d)
{
	year = y;
	month = m;
	day = d;
}

void Date::next() {
	// Leap year
	if (year % 4 == 0) {
		daysPerMonth[2 - 1] = 29;
	}
	// Last day in month
	if (day == daysPerMonth[month - 1]) {
		if (month == 12) { // December 31
			year += 1;
			month = 1;
		} else {
			month += 1;
		}
		day = 0;
	}
	day += 1;
}

istream& operator>>(istream& is, Date& dt)
{
	string s, y, m, d;
	is >> s;

//	cout << "y = " << y << "\n" << "m = " << m << "\n" << "d = " << d << endl;

	if (s[4] != '-' || s[7] != '-') {
		goto err;
	}

	try {
		y = s.substr(0, 4);
		m = s.substr(5, 2);
		d = s.substr(8, 2);

		int year = stoi(y);
		int month = stoi(m);
		int day = stoi(d);

		if ((month < 1 || 12 < month) ||
			(day < 1   || Date::daysPerMonth[(month - 1) % 12] < month))
		{
			goto err;
		}
		
		dt.setDate(year, month, day);

	} catch (const invalid_argument& e) {
//		cout << "Invalid argument!" << endl;
		goto err;

	} catch(const out_of_range& e) {
//		cout << "Out of range!" << endl;
		goto err;
	}

	return is;

err:
	is.setstate(ios_base::failbit);
	return is;
}

ostream& operator<<(ostream& os, const Date& dt)
{
	os << setw(4) << setfill('0') << dt.getYear() << '-';
	os << setw(2) << setfill('0') << dt.getMonth() << '-';
	os << setw(2) << setfill('0') << dt.getDay();
	return os;
}

