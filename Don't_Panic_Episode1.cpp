#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/



 
string getAction(int cloneFloor, int clonePos, string direction, int exitFloor, int exitPos, vector<vector<int>> v) {

	string action = "WAIT";
	if (cloneFloor != -1) {
		if (cloneFloor < exitFloor) {
			if ((clonePos < v[cloneFloor][0]) && (direction == "LEFT")) {
				action = "BLOCK";
			}
			if ((clonePos > v[cloneFloor][0]) && (direction == "RIGHT")) {
				action = "BLOCK";
			}
		}
		else {
			if ((clonePos < exitPos) && (direction == "LEFT")) {
				action = "BLOCK";
			}
			if ((clonePos > exitPos) && (direction == "RIGHT")) {
				action = "BLOCK";
			}
		}
	}
	

	return action;
}
 
int main()
{
    int nbFloors; // number of floors
    int width; // width of the area
    int nbRounds; // maximum number of rounds
    int exitFloor; // floor on which the exit is found
    int exitPos; // position of the exit on its floor
    int nbTotalClones; // number of generated clones
    int nbAdditionalElevators; // ignore (always zero)
    int nbElevators; // number of elevators
    cin >> nbFloors >> width >> nbRounds >> exitFloor >> exitPos >> nbTotalClones >> nbAdditionalElevators >> nbElevators; cin.ignore();
    vector<vector<int>> vElevators;
	vElevators = vector<vector<int>>(nbFloors);
    for(int i=0;i<nbFloors;i++){
     vector<int> v;
     vElevators.push_back(v);
    }
    for (int i = 0; i < nbElevators; i++) {
        int elevatorFloor; // floor on which this elevator is found
        int elevatorPos; // position of the elevator on its floor
        cin >> elevatorFloor >> elevatorPos; cin.ignore();
        vElevators[elevatorFloor].push_back(elevatorPos);
    }

    // game loop
    while (1) {
        int cloneFloor; // floor of the leading clone
        int clonePos; // position of the leading clone on its floor
        string direction; // direction of the leading clone: LEFT or RIGHT
        cin >> cloneFloor >> clonePos >> direction; cin.ignore();
		string action = getAction(cloneFloor,clonePos,direction,exitFloor,exitPos,vElevators);
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        cout << action << endl; // action: WAIT or BLOCK
    }
}