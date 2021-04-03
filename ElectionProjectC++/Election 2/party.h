#pragma once
#include "Citizen_list.h"
#include <string.h>
#include <iostream>
#include <typeinfo>

using namespace std;

class party
{
private:
	string name;
	citizen* leader;
	Citizen_list* rep_list_by_district;
	int size;
	
public:
	party();
	party(string& name, citizen* leader);//fix, now gets name&
	party(const party& other);
	~party();
	bool addRep(citizen* c, int districtId);
	void enlargeRepList();//מגדיל גם את סייז וגם עושה ריאלוק למערך 
	bool setName(string name);
	string getName();
	bool setLeader(citizen* leader);
	citizen* getLeader();
	void set_rep_list_and_size(int s);//מקבל גודל ואז מגדיל את המערך ומעדכן את סייז בהתאם

	friend ostream& operator<<(ostream& os, const party& p)
	{

		os << " Name of party: " << p.name << " - " << "leader: " << p.leader->getName() << "\nthe reps:\n";
		for (int i = 0; i < p.size; i++)
		{
			os << p.rep_list_by_district[i] << endl;//printing the reps by district
		}

		return os;
	}
	void getListInIndex(int index, int totalReps);
	citizen* getRep(int district, int repIndex);

	//file handling:
	void saveParty(ofstream& file);
	void loadParty(ifstream& file, Citizen_list& mainList);

};
