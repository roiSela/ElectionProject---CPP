#include "date.h"

Date::Date() {
	day = 0;
	month = 0;
	year = 0;
}

void Date::saveDate(ofstream& file)
{
	file.write(reinterpret_cast<char*>(&day), sizeof(int));
	file.write(reinterpret_cast<char*>(&month), sizeof(int));
	file.write(reinterpret_cast<char*>(&year), sizeof(int));
}

void Date::loadDate(ifstream& file)
{
	file.read(reinterpret_cast<char*>(&day), sizeof(int));
	file.read(reinterpret_cast<char*>(&month), sizeof(int));
	file.read(reinterpret_cast<char*>(&year), sizeof(int));
}
