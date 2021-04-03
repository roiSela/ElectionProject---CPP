#include "citizen.h"
const int rightid = 9;
//citizen::citizen()
//{
//	this->name = nullptr;
//	this->district_id = -1;
//	this->id = -1;
//	this->yearOfBirth =-1;
//	this->voted = false;
//}

citizen::citizen()
{
	Setdistrict_id(-1);
	setID(-1);
	setyearOfBirth(-1);
	this->voted = false;
}

citizen::citizen( char* name,  int district_id,long int id,  int yearOfBirth) {
	if (countDigit(id)!=rightid)
	{
		throw "invalid input,the id of the citizen must be 9 digits long";
	}
	Setdistrict_id(district_id);
	setID(id);
	setyearOfBirth(yearOfBirth);
	this->voted = false;
}

citizen::citizen(const string name, const int district_id, const long int id, const int yearOfBirth) {
	if (countDigit(id) != rightid)
	{
		throw "invalid input,the id of the citizen must be 9 digits long";
	}
	this->name = name;
	this->district_id = district_id;
	this->id = id;
	this->yearOfBirth = yearOfBirth;
	this->voted = false;
}

citizen:: citizen(const citizen& c)
{
	this->name =c.name;
	this->district_id = c.district_id;
	this->id = c.id;
	this->yearOfBirth = c.yearOfBirth;
	this->voted = c.voted;
}


string& citizen::getName()
{
	return this->name;
}

bool citizen::setName(string name)
{
	this->name = name;
	return true;
}

bool citizen::setName(char* name) {
	this->name = name;
	return true;
}

int& citizen::Getdistrict_id()
{
	return this->district_id;
}
bool citizen::Setdistrict_id(int district_id)
{
	this->district_id = district_id;
	return true;
}

long int& citizen::getID()
{
	return this->id;
}
bool citizen::setID(long int id)
{
	this->id = id;
	return true;
}

int& citizen::getyearOfBirth()
{
	return this->yearOfBirth;
}
bool citizen::setyearOfBirth(int yearOfBirth)
{
	this->yearOfBirth = yearOfBirth;
	return true;
}


citizen& citizen:: operator=(citizen& other)
{
	this->name = other.name;
	this->district_id = other.district_id;
	this->id = other.id;
	this->yearOfBirth = other.yearOfBirth;
	this->voted = other.voted;
	return (*this);
}


void citizen::saveCitizen(ofstream& file)
{


	int len = name.length();	
	file.write(reinterpret_cast<char*> (&len), sizeof(int));
	file.write(name.c_str(), len);


	file.write(reinterpret_cast<char*>(&district_id), sizeof(int));
	file.write(reinterpret_cast<char*>(&id), sizeof(long int));
	file.write(reinterpret_cast<char*>(&yearOfBirth), sizeof(int));
	file.write(reinterpret_cast<char*>(&voted), sizeof(bool));
}

void citizen::saveCitizenID(ofstream& file)
{
	file.write(reinterpret_cast<char*>(&id), sizeof(long int));
}

void citizen::loadCitizen(ifstream& file)
{
	int len;
	file.read(reinterpret_cast<char*> (&len), sizeof(int));
	char* temp = new char[len + 1];
	file.read(temp, len);
	temp[len] = '\0';
	name = temp;
	delete[] temp;

	file.read(reinterpret_cast<char*>(&district_id), sizeof(int));
	file.read(reinterpret_cast<char*>(&id), sizeof(long int));
	file.read(reinterpret_cast<char*>(&yearOfBirth), sizeof(int));
	file.read(reinterpret_cast<char*>(&voted), sizeof(bool));
}
