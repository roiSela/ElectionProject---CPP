#include "party_data.h"
party_data::party_data()
{
	this->indexOfParty = 0;
	this->totalRepsForParty = 0;
	this->totalVotersForParty = 0;
	this->percentOfVotes = 0;
}

void party_data:: AddToVotes(int Toadd)
{
	totalVotersForParty = totalVotersForParty + Toadd;
}
void party_data:: AddToReps(int Toadd)
{
	totalRepsForParty = totalRepsForParty + Toadd;

}
void party_data::udateIndex(int index)
{
	this->indexOfParty = index;
}

void party_data:: mergeSort(party_data* pointers, unsigned int size)
{
	// Variables:
	party_data* temp;
	unsigned int i;
	// Code:
	if (size <= 1)
	{ // If size <= 1 or array is already sorted then do nothing.
		return;
	}
	else
	{ // If the size is greater then one:
		mergeSort(pointers, size / 2);
		mergeSort(pointers + (size / 2), size - (size / 2));
		temp = new party_data [size];
		merge(pointers, size / 2, pointers + (size / 2), size - (size / 2), temp);
		for (i = 0; i < size; i++)
		{
			pointers[i] = temp[i];
		}
		delete[]temp;
	}

}
void party_data::merge(party_data* pointers1, unsigned int size1, party_data* pointers2, unsigned int size2, party_data* temp)
{
	// Variables:
	unsigned int i1 = 0, i2 = 0, tempIndex = 0;
	// Code:
	while ((i1 < size1) && (i2 < size2))
	{
		if (pointers1[i1].getReps() >= pointers2[i2].getReps())
		{
			temp[tempIndex] = pointers1[i1];
			i1++;
		}
		else
		{
			temp[tempIndex] = pointers2[i2];
			i2++;
		}
		tempIndex++;

	}
	while (i1 < size1)
	{
		temp[tempIndex] = pointers1[i1];
		i1++;
		tempIndex++;
	}
	while (i2 < size2)
	{
		temp[tempIndex] = pointers2[i2];
		i2++;
		tempIndex++;
	}

}



void party_data::Simple_mergeSort(party_data* pointers, unsigned int size)
{

	// Variables:
	party_data* temp;
	unsigned int i;
	// Code:
	if (size <= 1)
	{ // If size <= 1 or array is already sorted then do nothing.
		return;
	}
	else
	{ // If the size is greater then one:
		Simple_mergeSort(pointers, size / 2);
		Simple_mergeSort(pointers + (size / 2), size - (size / 2));
		temp = new party_data[size];
		Simple_merge(pointers, size / 2, pointers + (size / 2), size - (size / 2), temp);
		for (i = 0; i < size; i++)
		{
			pointers[i] = temp[i];
		}
		delete[]temp;
	}
}
void  party_data::Simple_merge(party_data* pointers1, unsigned int size1, party_data* pointers2, unsigned int size2, party_data* temp)
{
	// Variables:
	unsigned int i1 = 0, i2 = 0, tempIndex = 0;
	// Code:
	while ((i1 < size1) && (i2 < size2))
	{
		if (pointers1[i1].getVotes() >= pointers2[i2].getVotes())
		{
			temp[tempIndex] = pointers1[i1];
			i1++;
		}
		else
		{
			temp[tempIndex] = pointers2[i2];
			i2++;
		}
		tempIndex++;

	}
	while (i1 < size1)
	{
		temp[tempIndex] = pointers1[i1];
		i1++;
		tempIndex++;
	}
	while (i2 < size2)
	{
		temp[tempIndex] = pointers2[i2];
		i2++;
		tempIndex++;
	}

}



