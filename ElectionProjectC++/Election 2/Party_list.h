#pragma once
#include "party.h"
#include <typeinfo>
class Party_list
{
private:
	party** partyArr;
	int Lsize, Psize;
public:
	Party_list();
	~Party_list();
	int getLsize() { return Lsize; }
	int getPsize() { return Psize; }
	bool addParty(string& name, long int id_of_candidate, Citizen_list the_list);
	bool addParty(string& name, long int id_of_candidate, Citizen_list the_list, int districtSize);
	bool realloc_partyArr();
	bool addParty(party* newParty);

	friend ostream& operator<<(ostream& os, const Party_list& list) {
		for (int i = 0; i < list.Lsize; i++) {
			cout << "party id: "<<i;//the party id is its name on the party list
			party* dst = list.partyArr[i];
			os << (*(dst)) << endl;
		}
		return os;
	}
	party** getPartyArr() { return this->partyArr; }
	string getNameOfPartyInParticilurIndex(int index);
	citizen* getPartyLeaderInParticilurIndex(int index);
	citizen* getRep(int partyIndex, int districtIndex, int repIndex);////////////////////////////////////////////////////
	void getRepsList(int partyIndex,int districtIndex,int totalReps);

	void savePartyList(ofstream& file);
	void loadPartyList(ifstream& file, Citizen_list& mainList);
	void checkMemoryAllocation(void* ptr)
	{
		if (ptr == nullptr)
		{
			throw "could not allocate memory";
		}
	}
};
