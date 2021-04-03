#pragma once
#include <typeinfo>
class party_data
{
private:
	int totalVotersForParty;
	int totalRepsForParty;
	int  indexOfParty;//the indexes of the parties in the parties arr that in this app
	float percentOfVotes;// only in use when the election is a simple one
public:
	party_data();
	void AddToVotes(int Toadd);
	void AddToReps(int Toadd);
	void udateIndex(int index);

	
	void setPercentOfVotes(float percent) { percentOfVotes = percent; }

	int getVotes() { return this->totalVotersForParty; }
	int getReps() { return this->totalRepsForParty; }
	int getIndex() { return this->indexOfParty; }
	
	float getPercentOfVotes() { return this->percentOfVotes; }

	void mergeSort(party_data* pointers, unsigned int size);
	void merge(party_data* pointers1, unsigned int size1, party_data* pointers2, unsigned int size2, party_data* temp);

	void Simple_mergeSort(party_data* pointers, unsigned int size);//merge sort for simple election
	void Simple_merge(party_data* pointers1, unsigned int size1, party_data* pointers2, unsigned int size2, party_data* temp);
};

