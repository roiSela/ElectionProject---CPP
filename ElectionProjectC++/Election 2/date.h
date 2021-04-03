#pragma once
#include <iostream>
#include <fstream>
#include <typeinfo>
using namespace std;

class Date
{
private:
	int day, month, year;
public:
	Date();

	friend istream& operator>>(istream& is, Date& c) {
		is >> c.day >> c.month >> c.year;

		if (c.year<=0)
		{
			throw "the year must be a positive number";
		}
		if (!((c.month>=1)&& (c.month <= 12)))
		{
			throw "invalid input,there are only 12 months";
		}
		else
		{
			if (c.month == 2)
			{
				if (!((c.day >= 1) && (c.day <= 28)))
				{
					throw "invalid input,in the month of february there are 28 days";
				}
			}
			else
			{
				if (!((c.day >= 1) && (c.day <= 30)))
				{
					throw "invalid input,there are just 30 days in a month (in expition to february)";
				}
			}

			
		}
	
		
		return is;
	}

	friend ostream& operator<<(ostream& os,const Date& c) {
		os << c.day << "/" << c.month << "/" << c.year;
		return os;
	}
	void saveDate(ofstream& file);
	void loadDate(ifstream& file);
	int getDay() { return day; }
	int getmonth() { return month; }
	int getyear() { return year; }
};


