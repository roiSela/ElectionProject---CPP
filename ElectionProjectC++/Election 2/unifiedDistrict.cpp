#include "unifiedDistrict.h"
void unifiedDistrict::saveDistrict(ofstream& file)
{
	//first we need to save the type of the district
	string s = typeid(unifiedDistrict).name();
	int len1 = s.size();
	file.write(reinterpret_cast<char*> (&len1), sizeof(int));
	file.write(s.c_str(),s.size());
	/// ///
	
	int len = district_name.length();
	file.write(reinterpret_cast<char*> (&len), sizeof(int));
	file.write(district_name.c_str(), len);

	file.write(reinterpret_cast<char*>(&district_id), sizeof(int));
	file.write(reinterpret_cast<char*>(&district_reps), sizeof(int));
	file.write(reinterpret_cast<char*>(&total_voters), sizeof(int));
	file.write(reinterpret_cast<char*>(&percent_voted), sizeof(float));
	int l = votes.size();
	file.write(reinterpret_cast<char*>(&(l)), sizeof(int));

	for (int i = 0; i < l; i++)
	{
		int solo;
		solo = votes[i];
		file.write(reinterpret_cast<char*>(&(solo)), sizeof(int));
	}

	file.write(reinterpret_cast<char*>(&how_many_people_voted_in_this_district), sizeof(int));
	valid_voters.saveCitizenListID(file);
	chosen_reps.saveCitizenListID(file);
}

void unifiedDistrict::loadDistrict(ifstream& file, Citizen_list& mainList)
{

	int len;
	file.read(reinterpret_cast<char*> (&len), sizeof(int));
	char* temp = new char[len + 1];
	file.read(temp, len);
	temp[len] = '\0';
	district_name = temp;
	delete[] temp;

	file.read(reinterpret_cast<char*>(&district_id), sizeof(int));
	file.read(reinterpret_cast<char*>(&district_reps), sizeof(int));
	file.read(reinterpret_cast<char*>(&total_voters), sizeof(int));
	file.read(reinterpret_cast<char*>(&percent_voted), sizeof(float));

	int l;
	file.read(reinterpret_cast<char*>(&l), sizeof(int));
	votes.resize(l);
	for (int i = 0; i < l; i++)
	{
		int solo;
		file.read(reinterpret_cast<char*>(&solo), sizeof(int));
		votes[i] = solo;
	}

	file.read(reinterpret_cast<char*>(&how_many_people_voted_in_this_district), sizeof(int));
	valid_voters.loadCitizenListID(file, mainList);
	chosen_reps.loadCitizenListID(file, mainList);
}

