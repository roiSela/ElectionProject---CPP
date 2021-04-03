#pragma once
#include <string.h>
#include <iostream>
#include <fstream>
#include "BSearch.h"
#include <typeinfo>
using namespace std;

class citizen
{
private:
	string name;
	int district_id;
	long int id;
	int yearOfBirth;
	bool voted;
public:
	//citizen();
	citizen();
	citizen(char* name, int district_id, long int id, int yearOfBirth);
	citizen(const string name,const int district_id,const long int id, const int yearOfBirth);//fix, added const
	citizen(const citizen& c);//fix, a copy constructor implementation

	string& getName();//fix,now return name2& instead of name2
	bool setName(char* name);
	bool setName(string name);

	int& Getdistrict_id();
	bool Setdistrict_id(int district_id);

	long int& getID();
	bool setID(long int id);

	int& getyearOfBirth();
	bool setyearOfBirth(int yearOfBirth);

	friend ostream& operator<<(ostream& os, const citizen& c)
	{
		os << "Name: " << c.name << " - " << "ID: " << c.id << ", " << "Birth year: " << c.yearOfBirth << ", " << "District ID: " << c.district_id << endl;
		return os;
	}

	citizen& operator=(citizen& other);

	bool getVoted() { return voted; }
	bool setVoted(bool op) { voted = op; return true; }

	//file handling:
	void saveCitizen(ofstream& file);
	void saveCitizenID(ofstream& file);
	void loadCitizen(ifstream& file);
	int countDigit(long int n)
	{
		int count = 0;
		while (n != 0)
		{
			n = n / 10;
			++count;
		}
		return count;
	}

};