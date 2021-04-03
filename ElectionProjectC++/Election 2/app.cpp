#include "app.h"

using namespace std;


void app::addDistrict() {
	string name;
	int reps;
	bool isSplit;
	if (isSimpleElection == true) {
		name = "onlyDistrict";
		isSplit = true;
	}
	else {
		cout << "Please enter the district name:" << endl;
		cin >> name;
		cout << "Please enter the district type , enter 1 for split and 0 for regular:" << endl;
		cin >> isSplit;
	}
	cout << "Please enter the number of representatives:" << endl;
	cin >> reps;
	try
	{
		this->districts.addDistrict(name, reps, isSplit);
		//when adding a new district we must update its votes arr acordingly to the other districts:
		abstractDistrict** arr = districts.getdistrictArr();
		arr[(districts.getLsize() - 1)]->set_votes_and_votes_size(parties.getLsize());

		//we need to update the parties acoordingly:
		party** temp = parties.getPartyArr();
		for (int i = 0; i < parties.getLsize(); i++)
		{
			temp[i]->enlargeRepList();
		}
		
	}
	catch(const char * msg)
	{
		cout << msg << endl;
		return;
	}
	
	
}


void app::addCitizen() {
	string name;
	int citizenID, districtID, birthYear;
	cout << "Please enter the name of the citizen:" << endl;
	cin >> name;
	cout << "Please enter the ID number of the citizen:" << endl;
	cin >> citizenID;
	cout << "Please enter the birth year of the citizen:" << endl;
	cin >> birthYear;
	if (isSimpleElection == true) {
		districtID = 0;
	}
	else {
		cout << "Please enter the district ID the citizen is located in:" << endl;
		cin >> districtID;
	}

	if (districtID >= districts.getLsize()) {
		cout << "The district you chose isn't on the district list, please add the district to the list first." << endl;
		return;
	}
	else {
		try
		{
			if (((date.getyear())- (birthYear))<18)
			{
				throw "age must be at least 18 years old";
			}
			this->citizens.addCitizen(name, citizenID, birthYear, districtID);
			this->districts.addVoter(citizens[citizens.getLsize()-1]);
			this->citizens.setSorted(false);

		}
		catch (const char* msg)
		{
			cout << msg << endl;
			return;
		}
		
	}
}

void app::addParty() {
	string name;
	int leaderID;
	cout << "Please enter the name of the party:" << endl;
	cin >> name;
	cout << "Please enter the ID number of the party leader:" << endl;
	cin >> leaderID;

	try
	{
		//we need to update the rep list of the new party	
		parties.addParty(name, leaderID, citizens,districts.getLsize());
		//when adding a new party the "votes" array in all the districts must be incremented:
		abstractDistrict** arr = districts.getdistrictArr();
		for (int i = 0; i < districts.getLsize(); i++)
		{
			arr[i]->inLargevotes();
		}

	}
	catch (const char* msg)
	{
		cout << msg << endl;
		return;
	}

}

void app::addRep() {
	int partyNum;
	int repID;
	int districtID;
	cout << "Please enter the ID of the rep:" << endl;
	cin >> repID;

	//first we do the regularity check
	try
	{

		if (!citizens.getSorted()) {
			citizens.mergeSort(citizens.getCitizenArr(), citizens.getLsize());
		}
		citizen* tempCitizen = citizens.binarySearch(citizens.getCitizenArr(), 0, citizens.getLsize() - 1, repID);
		if (tempCitizen == nullptr)
		{
			throw "The rep id you chose isn't on the citizen list, please add the citizen to the list first.";
		}
		else
		{
			cout << "Please enter the party number:" << endl;
			cin >> partyNum;
			if (partyNum >= parties.getLsize()) {
				throw "The party you chose isn't on the party list, please add the party to the list first.";
			}
			else
			{

				cout << "Please enter the district ID:" << endl;
				cin >> districtID;

				if (isSimpleElection == false)
				{
					if (districtID >= districts.getLsize()) {
						cout << "The district you chose isn't on the district list, please add the district to the list first." << endl;
					}
					else
					{
						//if we got here we know that the input is ok
						party** arr = parties.getPartyArr();
						arr[partyNum]->addRep(tempCitizen, districtID);
					}
				}
				else//in a simple election there is are no districts
				{
					districtID = 0;//we need all the parties to be within the same "district"
					party** arr = parties.getPartyArr();
					arr[partyNum]->addRep(tempCitizen, districtID);
				}

			}

		}

	}
	catch (const char* msg)
	{
		cout << msg << endl;
		return;
	}


}

void app::printDistricts() {
	cout << districts;
}

void app::printCitizens() {
	cout << citizens;
}

void app::printParties() {
	cout << parties;
}

void app::vote() {
	long int id;
	int party_number;
	try
	{

		if (!citizens.getSorted())
			citizens.mergeSort(citizens.getCitizenArr(), citizens.getLsize());

		cout << "Please enter the ID number of the voter:" << endl;
		cin >> id;
		citizen* voter = citizens.binarySearch(id);
		if (voter==nullptr)
		{
			throw "This citizen is not in the citizens list";
		}
		if (voter->getVoted()) {
			throw "This citizen already voted" ;
		}
		else {
			cout << "Please enter the party number you'd like to vote for:" << endl;
			cin >> party_number;
			if (party_number >= parties.getLsize())
				throw "This party doesn't exist.";
			else {
				//if we got here we know that the input is ok
				voter->setVoted(true);
				districts.addVoteToDistrict(party_number, voter->Getdistrict_id());

			}

		}

	}
	catch (const char* msg)
	{
		cout << msg << endl;
		return;
	}


}

void app::printResults()
{
	//variables related to district calc:
	float percentVoted;
	abstractDistrict** arr = districts.getdistrictArr();
	//variables related to static party calc:
	int numOfParties = parties.getLsize();
	vector<int>  repsNum;
	DynamicArray<float> percentOfVotes;
	int maxIndex, maxVoters;
	//percentOfVotes.resize(numOfParties);
	for (int i = 0; i < numOfParties; i++)
	{
		percentOfVotes.push_back(0);
	}

	party_data* total_arr;
	total_arr = new party_data[numOfParties];
	//variables for all around calc's to see who won
	try
	{	
		checkMemoryAllocation(total_arr);

	}
	catch (const char* msg)
	{
		cout << msg << endl;
		return;
	}
	
	//print districts:
	for (int i = 0; i < districts.getLsize(); i++)
	{
		cout << "-----------------------------------------------------------------" << endl;
		maxIndex = 0;
		maxVoters = 0;

		percentVoted = 100 * ((float)(arr[i]->getNumOf_how_many_people_voted_in_this_district())) / ((float)(arr[i]->getTotalVoters()));
		districts.setPercentVotedInDistrict(i, percentVoted);
		repsNum = calculateReps(i);

		/////////////////////////////////////////////////////
		for (int partyIndex = 0; partyIndex < parties.getLsize(); partyIndex++)
		{
			for (int j = 0; j < repsNum[partyIndex]; j++) 
			{
				arr[i]->addRep(parties.getRep(partyIndex, i, j));
			}
		}
		/////////////////////////////////////////////////////
		
		if (typeid(*(districts[i])) == typeid(splitDistrict))// if the district is a split district (or not), we must distribute the reps accordingly
		{
			party_data* temp;//temp will be used to contain how much reps each party got from this district (it will be deleted and alocted each new split district)
			temp = new party_data[numOfParties];

			for (int j = 0; j < numOfParties; j++)
			{
				percentOfVotes[j] = 100 * (arr[i]->calculatePercentOfVotes(j));
				if (repsNum[j] > maxVoters)//this is how we know which party won this district
				{
					maxIndex = j;
					maxVoters = repsNum[j];
				}
				total_arr[j].AddToReps(repsNum[j]);
				total_arr[j].AddToVotes(arr[i]->getDataInVoteIndex(j));// we update how many people in the current district(i) voted for the current party (j); 
				total_arr[j].udateIndex(j); // we put j variable inside of total arr in the j place,for sorting purposes

				temp[j].AddToReps(repsNum[j]);
				temp[j].udateIndex(j); // we put j variable inside of total arr in the j place,for sorting purposes
			}

			cout << "in the district of " << arr[i]->getName() << " " << percentVoted << "% of the citizens voted." << endl;
			for (int j = 0; j < numOfParties; j++)
			{
				cout << arr[i]->getDataInVoteIndex(j) << " as in:" << percentOfVotes[j];
				cout << " percent of voters," << " voted for " << parties.getNameOfPartyInParticilurIndex(j) << endl;
			}
			cout << "and that is why there will be:" << endl;
			for (int j = 0; j < numOfParties; j++)
			{
				cout << repsNum[j] << " reps for " << parties.getNameOfPartyInParticilurIndex(j) << endl;
				cout << "and those reps are:" << endl;

				try
				{

					parties.getRepsList(j, i, repsNum[j]);///
				}
				catch (const char* msg)
				{
					cout << msg << endl;
					return;
				}
				
			}

			//now we need to print all the canditates that the district gave them reps and how much reps there were given ,in a downgrading order.
			///
			//first lets sort the total_arr:
			temp[0].mergeSort(temp, numOfParties);
			if ((temp[0].getReps())==0)
			{
				cout << "no party got reps " <<endl;
			}
			else
			{
				int k=0;
				while ((temp[k].getReps())!=0)
				{
					citizen* leader = parties.getPartyLeaderInParticilurIndex(temp[k].getIndex());
					cout << "the party leader " << leader->getName() << " got " << temp[k].getReps() <<" reps "<< endl;
					k++;
				}
			}
			delete[] temp;
			cout << "-----------------------------------------------------------------" << endl;
		}
		else
		{
			for (int j = 0; j < numOfParties; j++)
			{
				percentOfVotes[j] = 100 * (arr[i]->calculatePercentOfVotes(j));
				if (repsNum[j] > maxVoters)//this is how we know which party won this district
				{
					maxIndex = j;
					maxVoters = repsNum[j];
				}
				
				total_arr[j].AddToVotes(arr[i]->getDataInVoteIndex(j)); // we update how many people in the current district(i) voted for the current party (j); 
				total_arr[j].udateIndex(j); // we put j variable inside of total arr in the j place,for sorting purposes
			}

			total_arr[maxIndex].AddToReps(districts.getNumOfDistrictRepsInIndex(i)); // we give all the reps of district to the party that got the most reps in this district

			cout << "in the district of " << arr[i]->getName() << " " << percentVoted << "% of the citizens voted." << endl;
			for (int j = 0; j < numOfParties; j++)
			{
				cout << arr[i]->getDataInVoteIndex(j) << " as in:" << percentOfVotes[j];
				cout << " percent of voters," << " voted for " << parties.getNameOfPartyInParticilurIndex(j) << endl;
			}
			cout << "and that is why there will be:" << endl;
			for (int j = 0; j < numOfParties; j++)
			{
				cout << repsNum[j] << " reps for " << parties.getNameOfPartyInParticilurIndex(j) << endl;
				cout << "and those reps are:" << endl;
				try
				{
					parties.getRepsList(j, i, repsNum[j]);///needs to add exciption check to this line 
				}
				catch (const char* msg)
				{
					cout << msg << endl;
					return;
				}
				
			}
			citizen* leader = parties.getPartyLeaderInParticilurIndex(maxIndex);
			cout << "and in this case,the district will give all of his " << arr[i]->getReps() << " reps for " << leader->getName() << endl;

			cout << "-----------------------------------------------------------------" << endl;
		}
		
	
	}


	//now we print the parties by order of reps:

	//first lest sort the total_arr:
	total_arr[0].mergeSort(total_arr, numOfParties);

	//now we will print the name of the party,its head,its reps and its votes.
	cout << "and has for the parties:" << endl;
	for (int i = 0; i < numOfParties; i++)
	{
		cout << "-----------------------------------------------------------------" << endl;
		citizen* leader = parties.getPartyLeaderInParticilurIndex(total_arr[i].getIndex());
		cout << "the party: " << parties.getNameOfPartyInParticilurIndex(total_arr[i].getIndex()) << endl;
		cout << " has the leader: " << leader->getName() << endl;
		cout << " it's number of reps is: " << total_arr[i].getReps() << endl;
		cout << " and it's num of votes in all the districts is: " << total_arr[i].getVotes() << endl;
		cout << "-----------------------------------------------------------------" << endl;
	}
	
	delete[] total_arr;
}

vector<int> app::calculateReps(int index) {
	abstractDistrict** arr = districts.getdistrictArr();
	vector<int> repsNum;
	repsNum.resize(parties.getLsize());
	vector<float> tempVotes;
	tempVotes.resize(parties.getLsize());

	for (int i = 0; i < parties.getLsize(); i++) {
		repsNum[i] = 0;
		tempVotes[i] = arr[index]->getDataInVoteIndex(i);
	}

	float votesPerRep = (float)(arr[index]->getNumOf_how_many_people_voted_in_this_district()) / (float)(arr[index]->getReps());
	int count = 0;
	while (count < arr[index]->getReps()) {
		float max = 0;
		int maxIndex = 0;
		for (int i = 0; i < parties.getLsize(); i++) {
			if (tempVotes[i] > max) {
				max = tempVotes[i];
				maxIndex = i;
			}
		}
		tempVotes[maxIndex] -= votesPerRep;
		repsNum[maxIndex]++;
		count++;
	}

	return repsNum;
}

void app::saveElection(string& fileName)
{
	ofstream file;
	try
	{
		file.open(fileName, ios::out | ios::binary);
		if (!file.is_open())
		{
			throw "File is not found";
		}

	}
	catch (const char* msg)
	{
		cout << msg << endl;
		return;
	}
	
	date.saveDate(file);
	file.write(reinterpret_cast<char*>(&isSimpleElection), sizeof(bool));
	citizens.saveCitizenList(file);
	districts.saveDistrictList(file);
	parties.savePartyList(file);
}

void app::loadElection(string& fileName)
{
	ifstream file;
	try
	{
		file.open(fileName, ios::in | ios::binary);
		if (!file.is_open())
		{
			throw "File is not found";		
		}

	}
	catch (const char* msg)
	{
		cout << msg << endl;
		return;
	}


	date.loadDate(file);
	file.read(reinterpret_cast<char*>(&isSimpleElection), sizeof(bool));
	citizens.loadCitizenList(file);
	districts.loadDistrictList(file, citizens);
	parties.loadPartyList(file, citizens);
}

void app::printResultsOfSimpleElection()
{
	//variables related to district calc:
	float percentVoted;
	abstractDistrict** arr = districts.getdistrictArr();
	//variables related to static party calc:
	int numOfParties = parties.getLsize();
	vector<int> repsNum;
	DynamicArray<float> percentOfVotes;
	for (int i = 0; i < numOfParties; i++)
	{
		percentOfVotes.push_back(0);
	}
	party_data* total_arr;
	total_arr = new party_data[numOfParties];
	//variables for all around calc's to see who won
	try
	{
		
		checkMemoryAllocation(total_arr);

	}
	catch (const char* msg)
	{
		cout << msg << endl;
		return;
	}
	
		
	////////////////////////////////////////////////////////////////////////////////////////////////////////////

		percentVoted = 100 * ((float)(arr[0]->getNumOf_how_many_people_voted_in_this_district())) / ((float)(arr[0]->getTotalVoters()));
		districts.setPercentVotedInDistrict(0, percentVoted);
		repsNum = calculateReps(0);
	
		for (int partyIndex = 0; partyIndex < parties.getLsize(); partyIndex++)
		{
			for (int j = 0; j < repsNum[partyIndex]; j++)
			{
				arr[0]->addRep(parties.getRep(partyIndex,0, j));
			}
		}	

			for (int j = 0; j < numOfParties; j++)
			{
				percentOfVotes[j] = 100 * (arr[0]->calculatePercentOfVotes(j));		
				total_arr[j].setPercentOfVotes(percentOfVotes[j]);
				total_arr[j].AddToReps(repsNum[j]);
				total_arr[j].AddToVotes(arr[0]->getDataInVoteIndex(j));// we update how many people in the current district(i) voted for the current party (j); 
				total_arr[j].udateIndex(j); // we put j variable inside of total arr in the j place,for sorting purposes
			}

			cout << "the total voting percentage is: " << percentVoted << endl;

	//now we print the parties by order of votes:

	//first lest sort the total_arr:
	total_arr[0].Simple_mergeSort(total_arr, numOfParties);

	for (int i = 0; i < numOfParties; i++)
	{
		cout << "-----------------------------------------------------------------" << endl;
		citizen* leader = parties.getPartyLeaderInParticilurIndex(total_arr[i].getIndex());
		cout << "the party: " << parties.getNameOfPartyInParticilurIndex(total_arr[i].getIndex()) << endl;
		cout << "has the leader: " << leader->getName() << endl;		
		cout << arr[0]->getDataInVoteIndex(i) << " as in: " << total_arr[i].getPercentOfVotes();
		cout << "percent of voters," << " voted for " << parties.getNameOfPartyInParticilurIndex(i) << endl;		
		cout << "it's number of reps is: " << total_arr[i].getReps() << endl;
		cout << "and those reps are:" << endl;
		try
		{

			parties.getRepsList(i, 0, repsNum[i]);// we must pay notice that repsNum[i] must be _equeal or smaller_ to the number of the reps we added to the party

		}
		catch (const char* msg)
		{
			cout << msg << endl;
			return;
		}
		
		cout << "and it's num of votes is: " << total_arr[i].getVotes() << endl;
		cout << "-----------------------------------------------------------------" << endl;
	}
	
	delete[] total_arr;
}

void app::chooseDateAndElectionType() {
	cout << "please enter the date for the elections (enter day month year)" << endl;
	int temp=1;
	while (temp==1)
	{
		try
		{
			temp = 0;
			cin >> date;
		}
		catch (const char* msg)
		{
			cout << msg << endl;
			cout << "please try again" << endl;
			temp = 1;
		}
	}
	
	
	cout << "Please enter the election type , enter 1 for simple and 0 for regular:" << endl;//to ask or if thats right
	cin >> isSimpleElection;
	if (isSimpleElection == true) {
		addDistrict();
	}
}

void app::show_menu() {
	int op = -1;
	string fileName;	
	enum state{Add_District = 1,Add_Citizen = 2, Add_Party = 3 ,Add_Party_Rep = 4,Print_all_Districts = 5,Print_all_Citizens = 6,Print_all_Parties = 7,Start_Vote = 8,Print_Results = 9, Exit_Program = 10,save_current_election=11,load_existing_election=12};
	

	cout << "Please choose an action:\n";
	while (op != Exit_Program) {
		cout << "1. Add District\n" << "2. Add Citizen\n" << "3. Add Party\n" << "4. Add Party Rep\n" << "5. Print all Districts\n";
		cout << "6. Print all Citizens\n" << "7. Print all Parties\n" << "8. Start Vote\n" << "9.Print Results\n" << "10.Exit Program\n" << "11. save current election\n" <<"12.load existing election" << endl;
		cin >> op;
		cin.ignore();
		switch (op)
		{
		case Add_District:
			if(isSimpleElection==true)
				cout << "ERROR,in a simple election there are no districts" << endl;
			else
				addDistrict();
			break;
		case Add_Citizen:
			addCitizen();
			break;
		case Add_Party:
			addParty();
			break;
		case Add_Party_Rep:
			addRep();
			break;
		case Print_all_Districts:
			if(isSimpleElection==true)
				cout << "ERROR,in a simple election there are no districts" << endl;
			else
				printDistricts();
			break;
		case Print_all_Citizens:
			printCitizens();
			break;
		case Print_all_Parties:
			printParties();
			break;
		case Start_Vote:
			vote();
			break;
		case Print_Results:
			cout << "the date is:" <<date<<endl;
			if (isSimpleElection == true)
				printResultsOfSimpleElection();
			else
				printResults();
			break;
		case Exit_Program:
			break;
		case save_current_election:
			cout << "please enter the file name:" << endl;
			cin >> fileName;
			saveElection(fileName);
			break;
		case load_existing_election:
			cout << "please enter the file name:" << endl;
			cin >> fileName;
			loadElection(fileName);
			break;
		default:
			cout << "Incorrect command," << endl;
			break;
			}
		cout << "Please choose another option:" << endl;
		}
	}

