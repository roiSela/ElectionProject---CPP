#include "Citizen_list.h"


Citizen_list::Citizen_list() {
	Lsize = 0;
	Psize = 2;
	isSorted = false;
	citizenArr = nullptr;
}

Citizen_list::~Citizen_list() {
	delete[] citizenArr;
}

Citizen_list::Citizen_list(const Citizen_list& c_list)
{
	this->Lsize= c_list.Lsize;
	this->Psize= c_list.Psize;
	this->isSorted= c_list.isSorted;
	this->citizenArr = new citizen*[Psize];
	for (int i = 0; i < Lsize; i++) {
		this->citizenArr[i] = c_list.citizenArr[i];
	}
}

int& Citizen_list::getLsize() {
	return this->Lsize;
}

bool Citizen_list::setLsize(int Lsize) {
	this->Lsize = Lsize;
	return true;
}

int& Citizen_list::getPsize() {
	return this->Psize;
}

bool Citizen_list::setPsize(int Psize) {
	this->Psize = Psize;
	return true;
}

bool Citizen_list::reallocCitizens() {
	citizen** newArr = new citizen * [Psize];
	checkMemoryAllocation(newArr);
	for (int i = 0; i < Lsize; i++) {
		newArr[i] = this->citizenArr[i];
	}
	delete[] this->citizenArr;
	this->citizenArr = newArr;
	return true;
}

bool Citizen_list::addCitizen(string name, int id, int yearOfBirth, int district_id) {
	citizen* newCitizen = new citizen(name, district_id, id, yearOfBirth);
	checkMemoryAllocation(newCitizen);
	if (Lsize == 0)
		this->citizenArr = new citizen * [1];
	this->Lsize++;

	if (Psize >= Lsize) {
		Psize *= 2;
		reallocCitizens();
	}
	this->citizenArr[Lsize - 1] = newCitizen;
	return true;
}

bool Citizen_list::addCitizen(citizen* newCitizen) {
	if (Lsize == 0)
		this->citizenArr = new citizen * [1];

	checkMemoryAllocation(this->citizenArr);
	this->Lsize++;

	if (Psize >= Lsize) {
		Psize *= 2;
		reallocCitizens();
	}
	this->citizenArr[Lsize - 1] = newCitizen;
	return true;
}

void Citizen_list::mergeSort(citizen** pointers, unsigned int size)
{
	// Variables:
	citizen** temp;
	unsigned int i;
	// Code:
	if (size <= 1 || isSorted)
	{ // If size <= 1 or array is already sorted then do nothing.
		return;
	}
	else
	{ // If the size is greater then one:
		mergeSort(pointers, size / 2);
		mergeSort(pointers + (size / 2), size - (size / 2));
		temp = new citizen * [size];
		merge(pointers, size / 2, pointers + (size / 2), size - (size / 2), temp);
		for (i = 0; i < size; i++)
		{
			pointers[i] = temp[i];
		}
		delete[]temp;
		setSorted(true);
	}
}
void  Citizen_list::merge(citizen** pointers1, unsigned int size1, citizen** pointers2, unsigned int size2, citizen** temp)
{
	// Variables:
	unsigned int i1 = 0, i2 = 0, tempIndex = 0;
	// Code:
	while ((i1 < size1) && (i2 < size2))
	{
		if ((*(pointers1[i1])).getID() <= (*(pointers2[i2])).getID())
		{
			temp[tempIndex] = pointers1[i1];
			i1++;
		}
		else
		{
			temp[tempIndex] = pointers2[i2];
			i2++;
		}
		tempIndex++;

	}
	while (i1 < size1)
	{
		temp[tempIndex] = pointers1[i1];
		i1++;
		tempIndex++;
	}
	while (i2 < size2)
	{
		temp[tempIndex] = pointers2[i2];
		i2++;
		tempIndex++;
	}
}

citizen* Citizen_list::binarySearch(citizen** arr, int l, int r, long int x)
{
	while (l <= r) {
		int m = l + (r - l) / 2;

		// Check if x is present at mid 
		if (arr[m]->getID() == x)
			return arr[m];

		// If x greater, ignore left half 
		if (arr[m]->getID() < x)
			l = m + 1;

		// If x is smaller, ignore right half 
		else
			r = m - 1;
	}

	// if we reach here, then element was 
	// not present 
	return nullptr;
}

citizen* Citizen_list::binarySearch(long int search) {
	int l = 0;
	int r = Lsize-1;
	while (l <= r) {
		int m = l + (r - l) / 2;

		// Check if x is present at mid 
		if (citizenArr[m]->getID() == search)
			return citizenArr[m];

		// If x greater, ignore left half 
		if (citizenArr[m]->getID() < search)
			l = m + 1;

		// If x is smaller, ignore right half 
		else
			r = m - 1;
	}

	// if we reach here, then element was 
	// not present 
	return nullptr;
}

citizen** Citizen_list::getCitizenArr()
{

	return (this->citizenArr);
}

citizen* Citizen_list::getCitizen(int index) {/////////////////////////////////////////////////////
	return citizenArr[index];
}

void Citizen_list::saveCitizenList(ofstream& file)
{
	file.write(reinterpret_cast<char*>(&Lsize), sizeof(int));
	file.write(reinterpret_cast<char*>(&Psize), sizeof(int));
	if (!isSorted)
		mergeSort(citizenArr, Lsize);
	for (int i = 0; i < Lsize; i++) {
		citizenArr[i]->saveCitizen(file);
	}
}

void Citizen_list::saveCitizenListID(ofstream& file)
{
	file.write(reinterpret_cast<char*>(&Lsize), sizeof(int));
	file.write(reinterpret_cast<char*>(&Psize), sizeof(int));
	for (int i = 0; i < Lsize; i++) {
		citizenArr[i]->saveCitizenID(file);
	}
}

void Citizen_list::loadCitizenList(ifstream& file)
{
	file.read(reinterpret_cast<char*>(&Lsize), sizeof(int));
	file.read(reinterpret_cast<char*>(&Psize), sizeof(int));
	citizenArr = new citizen* [Psize];
	for (int i = 0; i < Lsize; i++) {
		citizen* temp = new citizen;
		temp->loadCitizen(file);
		citizenArr[i] = temp;
	}
}

void Citizen_list::loadCitizenListID(ifstream& file, Citizen_list& mainList)
{
	file.read(reinterpret_cast<char*>(&Lsize), sizeof(int));
	file.read(reinterpret_cast<char*>(&Psize), sizeof(int));
	citizenArr = new citizen * [Psize];
	long int temp;
	for (int i = 0; i < Lsize; i++) {
		file.read(reinterpret_cast<char*>(&temp), sizeof(long int));
		citizenArr[i] = mainList.binarySearch(temp);
	}
}

Citizen_list& Citizen_list::operator=(const Citizen_list& other)
{
	this->Lsize = other.Lsize;
	this->Psize = other.Psize;
	this->isSorted = other.isSorted;
	this->citizenArr = new citizen*[Psize];
	for (int i = 0; i < Lsize; i++) {
		this->citizenArr[i] = other.citizenArr[i];
	}
	return *this;
}

citizen* Citizen_list::operator[](int index)
{
	if (index > Lsize)
		throw "Index out of bounds";
	else
		return citizenArr[index];
}
