#pragma once
#include <typeinfo>
#include "abstractDistrict.h"
#include <math.h>
#include "Citizen_list.h"
#include <vector>

class splitDistrict: public abstractDistrict
{

public:
	splitDistrict() {
		this->district_reps = 0;
		this->district_id = 0;
		this->total_voters = 0;
		this->percent_voted = 0;
		this->how_many_people_voted_in_this_district = 0;
	}

	splitDistrict(const string& name, int reps, int id)
	{
		this->district_name = name;
		this->district_reps = reps;
		this->district_id = id;
		this->total_voters = 0;
		this->percent_voted = 0;
		this->how_many_people_voted_in_this_district = 0;
	}

	friend ostream& operator<<(ostream& os, const  splitDistrict& district) {
		os << district.district_id << " - " << district.district_name << " - " << district.district_reps << " - split ";		
		return os;
	}

	void operator=(const splitDistrict& other)
	{
		this->district_name = other.district_name;
		this->district_reps = other.district_reps;
		this->district_id = other.district_id;
		this->total_voters = other.total_voters;
		this->percent_voted = other.percent_voted;
		this->chosen_reps = other.chosen_reps;
	}

	void saveDistrict(ofstream& file);
	void loadDistrict(ifstream& file, Citizen_list& mainList);


};

