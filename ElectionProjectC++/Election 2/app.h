#pragma once
#include "Citizen_list.h"
#include "DistrictList2.h"
#include "Party_list.h"
#include "party_data.h"
#include "date.h"
#include "dynamicArray.h"
#include <string.h>
#include <vector>
#include <fstream>
#include <typeinfo>
class app
{
private:
	Date date;
	Citizen_list citizens;
	DistrictList2 districts;
	Party_list parties;
	bool isSimpleElection;

	void addDistrict();
	void addCitizen();
	void addParty();
	void addRep();
	void printDistricts();
	void printCitizens();
	void printParties();
	void vote();
	void printResults();
	void printResultsOfSimpleElection();
	vector<int> calculateReps(int index);
	void saveElection(string& fileName);
	void checkMemoryAllocation(void* ptr)
	{
		if (ptr == nullptr)
		{
			throw "could not allocate memory";
		}
	}

public:
	void loadElection(string& fileName);
	void chooseDateAndElectionType();
	void show_menu();
};

