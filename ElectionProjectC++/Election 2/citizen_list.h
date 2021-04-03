#pragma once
#include "citizen.h"
#include <typeinfo>
class Citizen_list
{
private:
	citizen** citizenArr;
	int Lsize, Psize;
	bool isSorted;
public:
	Citizen_list();
	~Citizen_list();
	Citizen_list(const Citizen_list& c_list);//fix,ctor implementation
	citizen** getCitizenArr();
	bool setLsize(int Lsize);
	int& getLsize();
	bool setPsize(int Psize);
	int& getPsize();
	bool addCitizen(string name, int id, int yearOfBirth, int district_id);
	bool addCitizen(citizen* newCitizen);
	bool reallocCitizens();
	bool setSorted(bool op) { isSorted = op; return true; }
	bool getSorted() { return isSorted; }

	friend ostream& operator<<(ostream& os, Citizen_list& c)
	{
		for (int i = 0; i < c.Lsize; i++)
		{
			citizen* temp = c.citizenArr[i];
			os << *(temp);
		}
		return os;
	}

	void mergeSort(citizen** pointers, unsigned int size);
	void merge(citizen** pointers1, unsigned int size1, citizen** pointers2, unsigned int size2, citizen** temp);
	citizen* binarySearch(citizen** arr, int l, int r, long int x);
	citizen* binarySearch(long int search);
	citizen* getCitizen(int index);/////////////////////////////////////////////////////

	void saveCitizenList(ofstream& file);
	void saveCitizenListID(ofstream& file);
	void loadCitizenList(ifstream& file);
	void loadCitizenListID(ifstream& file, Citizen_list& mainList);

	void checkMemoryAllocation(void* ptr)
	{
		if (ptr == nullptr)
		{
			throw "could not allocate memory";
		}
	}

	Citizen_list& operator=(const Citizen_list& other);
	citizen* operator[](int index);
};
