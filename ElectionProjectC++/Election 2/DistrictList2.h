#pragma once
#include "splitDistrict.h"
#include "abstractDistrict.h"
#include "unifiedDistrict.h"
#include <typeinfo>
class DistrictList2
{
private:
	abstractDistrict** districtArr;
	int Lsize, Psize;
public:
	DistrictList2();
	~DistrictList2();
	bool addDistrict(const string& name, int district_reps, bool is_split);
	bool addVoter(citizen* newCitizen);
	bool reallocDistricts();
	void addVoteToDistrict(int party_index,int id);
	bool setPercentVotedInDistrict(int index,float percent_voted);
	friend ostream& operator<<(ostream& os, const DistrictList2& list) {
		for (int i = 0; i < list.Lsize; i++) {
			abstractDistrict* dst = list.districtArr[i];
			if (typeid(dst) == typeid(splitDistrict))
			{
				os << *(static_cast<splitDistrict*>(dst)) << endl;
			}
			else
			{
				os << *(static_cast<unifiedDistrict*>(dst)) << endl;
			}
			
		}
		return os;
	}
	abstractDistrict** getdistrictArr()
	{
		return districtArr;
	}
	
	int getLsize() { return Lsize; }

	int getNumOfDistrictRepsInIndex(int index); // gets the num of the reps that was assign to the district in the given index

	void saveDistrictList(ofstream& file);
	void loadDistrictList(ifstream& file, Citizen_list& mainList);

	void checkMemoryAllocation(void* ptr)
	{
		if (ptr == nullptr)
		{
			throw "could not allocate memory";
		}
	}

	abstractDistrict* operator[](int index);
};
