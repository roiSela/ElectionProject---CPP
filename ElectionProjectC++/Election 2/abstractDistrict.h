#pragma once

#include <math.h>
#include "Citizen_list.h"
#include <vector>
#include <typeinfo>
class abstractDistrict
{
protected:
	string district_name;
	int district_reps, district_id, total_voters;
	float percent_voted;
	Citizen_list valid_voters;
	Citizen_list chosen_reps;
	vector<int> votes;//every index indicates a party
	int how_many_people_voted_in_this_district;
public:
	abstractDistrict();	
	abstractDistrict(const string& name, int reps, int id);
    abstractDistrict(const abstractDistrict& other);
	
	bool incrementVoters();
	bool addToValidVoters(citizen* newCitizen);
	void inLargevotes();//this one we use to inlarge by one the districts votes list
	void set_votes_and_votes_size(int s);//this one we use when adding a new district and we already have a size
	void set_percent_voted(float percent_voted_input);
	void addvote(int index);
	const int getID() { return district_id; }//fix,now const
	const string& getName() { return district_name; }//fix,now const
	const int getReps() { return district_reps; }//fix,now const
	const int getNumOf_how_many_people_voted_in_this_district() { return how_many_people_voted_in_this_district; }//fix,now const
	const int getTotalVoters() { return  total_voters; }//fix,now const
	const float getPercentVoted() { return percent_voted; }//fix,now const
	const int getDataInVoteIndex(int index) { return votes[index]; }//fix,now const
	int calculateRelativeReps(int indexOfVotesArray);
	float calculatePercentOfVotes(int indexOfVotesArray);
	void addRep(citizen* rep);/////////////////////////////////////////////////////
	
};

