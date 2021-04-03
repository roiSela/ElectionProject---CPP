#include "DistrictList2.h"

//District2* districtArr;
//int Lsize, Psize;

DistrictList2::DistrictList2() {
	this->districtArr = nullptr;
	this->Psize = 2;
	this->Lsize = 0;
}

DistrictList2::~DistrictList2() {
	for (int i = 0; i < Lsize; i++) {
		delete this->districtArr[i];
	}
	delete[] this->districtArr;
}

bool DistrictList2::addDistrict(const string& name, int district_reps,bool is_split) {
	abstractDistrict* newDistrict;
	if (district_reps < 0)
	{
		throw "number of representatives cannot be a negitive number";
	}
	if (is_split)
	{
		newDistrict = new splitDistrict(name, district_reps, Lsize);
		
	}
	else
	{
		newDistrict = new unifiedDistrict(name, district_reps, Lsize);
		
	}
	checkMemoryAllocation(newDistrict);
	if (Lsize == 0)
		this->districtArr = new abstractDistrict * [1];

	checkMemoryAllocation(districtArr);
	this->Lsize++;
	if (Lsize >= Psize) {
		Psize *= 2;
		reallocDistricts();
	}
	this->districtArr[Lsize - 1] = newDistrict;
	return true;
}


bool DistrictList2::reallocDistricts() {
	abstractDistrict** newArr = new abstractDistrict * [Psize];
	checkMemoryAllocation(newArr);
	for (int i = 0; i < Lsize; i++) {
		newArr[i] = this->districtArr[i];
	}
	delete[] this->districtArr;
	this->districtArr = newArr;
	return true;
}

bool DistrictList2::addVoter(citizen* newCitizen) {
	this->districtArr[newCitizen->Getdistrict_id()]->incrementVoters();
	this->districtArr[newCitizen->Getdistrict_id()]->addToValidVoters(newCitizen);
	
	return true;
}

void DistrictList2::addVoteToDistrict(int party_index,int id)
{
	districtArr[id]->addvote(party_index);

}

bool DistrictList2:: setPercentVotedInDistrict(int index, float percent_voted)
{
	districtArr[index]->set_percent_voted(percent_voted);
	return true;
}



int DistrictList2::getNumOfDistrictRepsInIndex(int index)
{
	return districtArr[index]->getReps();
}

void DistrictList2::saveDistrictList(ofstream& file)
{
	file.write(reinterpret_cast<char*>(&Lsize), sizeof(int));
	file.write(reinterpret_cast<char*>(&Psize), sizeof(int));
	for (int i = 0; i < Lsize; i++) {
		if (typeid(*districtArr[i]) == (typeid(splitDistrict)))
		{
		
			static_cast<splitDistrict*>(districtArr[i])->saveDistrict(file);
		}
		else
		{
			
			static_cast<unifiedDistrict*>(districtArr[i])->saveDistrict(file);
		}
	}
}

void DistrictList2::loadDistrictList(ifstream& file, Citizen_list& mainList)
{
	file.read(reinterpret_cast<char*>(&Lsize), sizeof(int));
	file.read(reinterpret_cast<char*>(&Psize), sizeof(int));
	districtArr = new abstractDistrict* [Psize];
	for (int i = 0; i < Lsize; i++) {
		/* first we get the district type*/
    int length;
	file.read(reinterpret_cast<char*> (&length), sizeof(int));
	char* t = new char[length + 1];
	file.read(t, length);
	t[length] = '\0';
	string s = t;
	delete[] t;
	//////////////////////////
	abstractDistrict* temp;
	if (s==(typeid(splitDistrict).name()))
	{
		temp = new splitDistrict;
		static_cast<splitDistrict*>(temp)->loadDistrict(file, mainList);
	}
	else
	{
		temp = new unifiedDistrict;
		static_cast<unifiedDistrict*>(temp)->loadDistrict(file, mainList);
	}
		
		districtArr[i] = temp;
	}
}


abstractDistrict* DistrictList2::operator[](int index)
{
	if (index > Lsize)
		throw "Index out of bounds";
	else
		return (districtArr[index]);
}