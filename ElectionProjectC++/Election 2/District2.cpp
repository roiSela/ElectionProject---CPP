#include "District2.h"

//string district_name;
//int district_reps, district_id, total_voters;
//float percent_voted;
//citizen_list chosen_reps;
//citizen_list valid_voters;
//	int* votes;
//int size;

District2::District2() {
	//this->district_name = nullptr;
	this->district_reps = 0;
	this->district_id = 0;
	this->total_voters = 0;
	this->percent_voted = 0;
	this->isSplit = false;
	this->how_many_people_voted_in_this_district = 0;
}

District2::District2(const string& name, int reps, int id) {
	this->district_name = name;
	this->district_reps = reps;
	this->district_id = id;
	this->total_voters = 0;
	this->percent_voted = 0;
	this->how_many_people_voted_in_this_district = 0;
	this->isSplit = false;
}

District2::District2(const District2& other) {
	this->district_name = other.district_name;
	this->district_reps = other.district_reps;
	this->district_id = other.district_id;
	this->total_voters = other.total_voters;
	this->percent_voted = other.percent_voted;
	this->chosen_reps = other.chosen_reps;
	this->how_many_people_voted_in_this_district = 0;
	this->isSplit = other.isSplit;
}


void District2::operator=(const District2& other) {
	this->district_name = other.district_name;
	this->district_reps = other.district_reps;
	this->district_id = other.district_id;
	this->total_voters = other.total_voters;
	this->percent_voted = other.percent_voted;
	this->chosen_reps = other.chosen_reps;
}

bool District2::incrementVoters() {
	this->total_voters++;
	return true;
}

bool District2::addToValidVoters(citizen* newCitizen) {
	this->valid_voters.addCitizen(newCitizen);
	return true;
}

void  District2::inLargevotes()
{	
	votes.push_back(0);
}
void  District2::set_votes_and_votes_size(int s)
{
	votes.resize(s, 0);
}

void District2::addvote(int index)
{
	votes[index] = votes[index] + 1;
	how_many_people_voted_in_this_district = how_many_people_voted_in_this_district + 1;
}

void District2::set_percent_voted(float percent_voted_input)
{
	this->percent_voted = percent_voted_input;
}

int  District2::calculateRelativeReps(int indexOfVotesArray)
{
	float voters_for_party = (float)(votes[indexOfVotesArray]);
	float voters_in_total_in_this_district = (float)(how_many_people_voted_in_this_district);
	float tempPercent = ((voters_for_party) / (voters_in_total_in_this_district));
	int relativeRep = round(((tempPercent) * ((float)(district_reps))));
	return relativeRep;
}

float District2::calculatePercentOfVotes(int indexOfVotesArray)
{
	float voters_for_party = (float)votes[indexOfVotesArray];
	float voters_in_total_in_this_district = (float)(how_many_people_voted_in_this_district);
	float tempPercent = ((voters_for_party) / (voters_in_total_in_this_district));
	return tempPercent;
}

void District2::addRep(citizen* rep) {
	chosen_reps.addCitizen(rep);
}

void District2::saveDistrict(ofstream& file)
{

	int len = district_name.length();
	file.write(reinterpret_cast<char*> (&len), sizeof(int));
	file.write(district_name.c_str(), len);

	file.write(reinterpret_cast<char*>(&district_id), sizeof(int));
	file.write(reinterpret_cast<char*>(&district_reps), sizeof(int));
	file.write(reinterpret_cast<char*>(&total_voters), sizeof(int));
	file.write(reinterpret_cast<char*>(&isSplit), sizeof(bool));
	file.write(reinterpret_cast<char*>(&percent_voted), sizeof(float));
	int l=votes.size();
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

void District2::loadDistrict(ifstream& file, Citizen_list& mainList)
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
	file.read(reinterpret_cast<char*>(&isSplit), sizeof(bool));
	file.read(reinterpret_cast<char*>(&percent_voted), sizeof(float));

	int l;
	file.read(reinterpret_cast<char*>(&l), sizeof(int));
	votes.resize(l);
	for (int i = 0; i < l; i++)
	{
		int solo;
		file.read(reinterpret_cast<char*>(&solo),sizeof(int));
		votes[i] = solo;
	}
	
	file.read(reinterpret_cast<char*>(&how_many_people_voted_in_this_district), sizeof(int));
	valid_voters.loadCitizenListID(file, mainList);
	chosen_reps.loadCitizenListID(file, mainList);
}

bool  District2::set_isSplit(bool is_Split)
{
	this->isSplit = is_Split;
	return true;
}
