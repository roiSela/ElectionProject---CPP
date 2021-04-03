#include "abstractDistrict.h"

//string district_name;
//int district_reps, district_id, total_voters;
//float percent_voted;
//citizen_list chosen_reps;
//citizen_list valid_voters;
//	int* votes;
//int size;

abstractDistrict::abstractDistrict() {
	this->district_reps = 0;
	this->district_id = 0;
	this->total_voters = 0;
	this->percent_voted = 0;	
	this->how_many_people_voted_in_this_district = 0;
}

abstractDistrict::abstractDistrict(const string& name, int reps, int id) {
	this->district_name = name;
	this->district_reps = reps;
	this->district_id = id;
	this->total_voters = 0;
	this->percent_voted = 0;
	this->how_many_people_voted_in_this_district = 0;
}

abstractDistrict::abstractDistrict(const abstractDistrict& other) {
	this->district_name = other.district_name;
	this->district_reps = other.district_reps;
	this->district_id = other.district_id;
	this->total_voters = other.total_voters;
	this->percent_voted = other.percent_voted;
	this->chosen_reps = other.chosen_reps;
	this->how_many_people_voted_in_this_district = 0;
}


bool abstractDistrict::incrementVoters() {
	this->total_voters++;
	return true;
}

bool abstractDistrict::addToValidVoters(citizen* newCitizen) {
	this->valid_voters.addCitizen(newCitizen);
	return true;
}

void  abstractDistrict::inLargevotes()
{
	votes.push_back(0);
}
void  abstractDistrict::set_votes_and_votes_size(int s)
{
	votes.resize(s, 0);
}

void abstractDistrict::addvote(int index)
{
	votes[index] = votes[index] + 1;
	how_many_people_voted_in_this_district = how_many_people_voted_in_this_district + 1;
}

void abstractDistrict::set_percent_voted(float percent_voted_input)
{
	this->percent_voted = percent_voted_input;
}

int  abstractDistrict::calculateRelativeReps(int indexOfVotesArray)
{
	float voters_for_party = (float)(votes[indexOfVotesArray]);
	float voters_in_total_in_this_district = (float)(how_many_people_voted_in_this_district);
	float tempPercent = ((voters_for_party) / (voters_in_total_in_this_district));
	int relativeRep = round(((tempPercent) * ((float)(district_reps))));
	return relativeRep;
}

float abstractDistrict::calculatePercentOfVotes(int indexOfVotesArray)
{
	float voters_for_party = (float)votes[indexOfVotesArray];
	float voters_in_total_in_this_district = (float)(how_many_people_voted_in_this_district);
	float tempPercent = ((voters_for_party) / (voters_in_total_in_this_district));
	return tempPercent;
}

void abstractDistrict::addRep(citizen* rep) {
	chosen_reps.addCitizen(rep);
}

