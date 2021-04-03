#include "Party_list.h"


Party_list::Party_list() {
	this->partyArr = nullptr;
	this->Psize = 2;
	this->Lsize = 0;
}

Party_list::~Party_list() {
	for (int i = 0; i < Lsize; i++) {
		delete this->partyArr[i];
	}
	delete[] this->partyArr;
}

bool Party_list::addParty(string& name, long int id_of_candidate, Citizen_list the_list)
{
	//finding the canditate first:
	if (!the_list.getSorted()) {
		the_list.mergeSort(the_list.getCitizenArr(), the_list.getLsize());
	}


	party* newParty = new party(name, the_list.binarySearch(the_list.getCitizenArr(), 0, the_list.getLsize() - 1, id_of_candidate));
	checkMemoryAllocation(newParty);
	if (Lsize == 0)
		this->partyArr = new party * [1];

	checkMemoryAllocation(this->partyArr);
	Lsize++;
	if (Lsize >= Psize)
	{
		Psize *= 2;
		realloc_partyArr();
	}

	this->partyArr[Lsize - 1] = newParty;
	return true;
}


bool Party_list::addParty(string& name, long int id_of_candidate, Citizen_list the_list,int districtSize)
{
	//finding the canditate first:
	if (!the_list.getSorted()) {
		the_list.mergeSort(the_list.getCitizenArr(), the_list.getLsize());
	}


	party* newParty = new party(name, the_list.binarySearch(the_list.getCitizenArr(), 0, the_list.getLsize() - 1, id_of_candidate));
	newParty->set_rep_list_and_size(districtSize);
	checkMemoryAllocation(newParty);
	if (Lsize == 0)
		this->partyArr = new party * [1];

	checkMemoryAllocation(this->partyArr);
	Lsize++;
	if (Lsize >= Psize)
	{
		Psize *= 2;
		realloc_partyArr();
	}

	this->partyArr[Lsize - 1] = newParty;
	return true;
}


bool Party_list::addParty(party* newParty) {
	if (Lsize == 0)
		this->partyArr = new party * [1];

	checkMemoryAllocation(this->partyArr);
	Lsize++;
	if (Lsize >= Psize)
	{
		Psize *= 2;
		realloc_partyArr();
	}

	this->partyArr[Lsize - 1] = newParty;
	return true;
}

bool Party_list::realloc_partyArr()
{
	party** newArr = new party * [Psize];
	checkMemoryAllocation(newArr);
	for (int i = 0; i < Lsize - 1; i++) {
		newArr[i] = this->partyArr[i];
	}
	delete[] this->partyArr;
	this->partyArr = newArr;
	return true;
}

string  Party_list:: getNameOfPartyInParticilurIndex(int index)
{
	return (partyArr[index]->getName());
}

citizen* Party_list::getPartyLeaderInParticilurIndex(int index)
{
	return (partyArr[index]->getLeader());
}

citizen* Party_list::getRep(int partyIndex, int districtIndex, int repIndex) {/////////////////////////////////////////////////////
 return	partyArr[partyIndex]->getRep(districtIndex, repIndex);
}


void Party_list :: getRepsList(int partyIndex, int districtIndex, int totalReps)///
{
	partyArr[partyIndex]->getListInIndex(districtIndex,totalReps);
}

void Party_list::savePartyList(ofstream& file)
{
	file.write(reinterpret_cast<char*>(&Lsize), sizeof(int));
	file.write(reinterpret_cast<char*>(&Psize), sizeof(int));
	for (int i = 0; i < Lsize; i++) {
		partyArr[i]->saveParty(file);
	}
}

void Party_list::loadPartyList(ifstream& file, Citizen_list& mainList)
{
	file.read(reinterpret_cast<char*>(&Lsize), sizeof(int));
	file.read(reinterpret_cast<char*>(&Psize), sizeof(int));
	partyArr = new party * [Psize];
	for (int i = 0; i < Lsize; i++) {
		party* temp = new party;
		temp->loadParty(file, mainList);
		partyArr[i] = temp;
	}
}

