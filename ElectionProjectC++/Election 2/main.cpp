#include "app.h"

int main() {
	enum election { new_election = 1, load = 2, exit = 3 };
	int state = -1;
	app App;
	string fileName;
	cout << "please enter 1 for new elections,2 for loading existing election,and 3 for exit" << endl;
	cin >> state;
	while (state != exit) {
		cin.ignore();
		switch (state) {
		case new_election:
			App.chooseDateAndElectionType();
			App.show_menu();
			state = exit;
			break;
		case load:
			cout << "Please enter the file name:" << endl;
			cin >> fileName;
			App.loadElection(fileName);
			App.show_menu();
			state = exit;
			break;
		case exit:
			cout << "you have chosen to exit" << endl;
			break;
		default:
			cout << "Not a valid option" << endl;
		}
	}
}

