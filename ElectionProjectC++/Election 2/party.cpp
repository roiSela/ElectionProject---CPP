#include "party.h"


//string name;
//citizen& leader;
//citizen* rep_list;

party::party() {
	//this->name = nullptr;
	this->leader = nullptr;
	this->rep_list_by_district = nullptr;
	this->size = 0;
	
}

party::party(string& name, citizen* leader)
{
	if (leader==nullptr)
	{
		throw "The citizen id you chose isn't on the citizen list, please add the citizen to the list first.";
	}
	this->name = name;
	this->leader = leader;
	this->rep_list_by_district = nullptr;
	this->size = 0;

}

party::party(const party& other)
{
	this->name = other.name;
	this->leader = other.leader;
	this->rep_list_by_district = other.rep_list_by_district;
	this->size = other.size;
}

party::~party()
{
	delete[] this->rep_list_by_district;//possible ruining of pointers with every realloc?
}
bool party::setName(string name) {
	this->name = name;
	return true;
}

string party::getName() {
	return this->name;
}

bool party::setLeader(citizen* leader) {
	this->leader = leader;
	return true;
}

citizen* party::getLeader() {
	return this->leader;
}

//when adding a new district , we must also inlarge they array
void party::enlargeRepList()
{
	size++;
	Citizen_list* temp;
	temp = new Citizen_list[size];
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < rep_list_by_district[i].getLsize(); j++) {
			temp[i].addCitizen(rep_list_by_district[i].getCitizen(j));
		}
	}
	delete[] rep_list_by_district;
	rep_list_by_district = temp;
}

void party::set_rep_list_and_size(int s)
{
	this->size = s;
	Citizen_list* temp;
	temp = new Citizen_list[size];
	rep_list_by_district = temp;
}

//adding a new rep to list
bool party::addRep(citizen* c, int districtId)
{
	//inLargeRepList();
	rep_list_by_district[districtId].addCitizen(c);
	return true;

}


citizen* party::getRep(int district, int repIndex) {/////////////////////////////////////////////////////
	return rep_list_by_district[district].getCitizen(repIndex);
}

void party::getListInIndex(int index,int totalReps)
{
	if ((rep_list_by_district[index].getLsize())>=totalReps)
	{
		for (int i = 0; i < totalReps; i++)
		{
			cout << *(rep_list_by_district[index].getCitizen(i));
		}

	}
	else
	{
		throw "the party do not have enoght reps to complete these election";
	}
		
	
	
}

void party::saveParty(ofstream& file)
{
	int len = name.length();
	file.write(reinterpret_cast<char*> (&len), sizeof(int));
	file.write(name.c_str(), len);

	leader->saveCitizenID(file);

	file.write(reinterpret_cast<char*>(&size), sizeof(int)); // saving size of rep array by district array
	for (int i = 0; i < size; i++) {
		rep_list_by_district[i].saveCitizenListID(file);
	}


}

void party::loadParty(ifstream& file, Citizen_list& mainList)
{
	int len;
	file.read(reinterpret_cast<char*> (&len), sizeof(int));
	char* t = new char[len + 1];
	file.read(t, len);
	t[len] = '\0';
	name = t;
	delete[] t;

	long int temp;
	file.read(reinterpret_cast<char*>(&temp), sizeof(long int));//saving the leader's id
	leader = mainList.binarySearch(temp);

	file.read(reinterpret_cast<char*>(&size), sizeof(int)); // saving size of rep array by district array
	rep_list_by_district = new Citizen_list[size];
	for (int i = 0; i < size; i++) {
		rep_list_by_district[i].loadCitizenListID(file, mainList);
	}


}
