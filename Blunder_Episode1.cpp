#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

struct Case {
	char element;
	bool visited = false;
	int ligne;
	int colonne;
};

void debugBoard(int C,int L,vector<vector<Case>> board) {
	for (int i = 0; i < L; i++) {

		for (int j = 0; j < C; j++) {

			cerr << board[i][j].element;

		}
		cerr << endl;

	}
}

void initLetterDirection(map<char, string>& letterDirection) {

	letterDirection['S'] = "SOUTH";
	letterDirection['E'] = "EAST";
	letterDirection['N'] = "NORTH";
	letterDirection['W'] = "WEST";
}

void initDirPriority(map<bool, map<int, string>>& dirPriorityInversorState) {

	map<int, string> dirPriority0;
	dirPriority0[1] = "SOUTH";
	dirPriority0[2] = "EAST";
	dirPriority0[3] = "NORTH";
	dirPriority0[4] = "WEST";

	map<int, string> dirPriority1;
	dirPriority1[4] = "SOUTH";
	dirPriority1[3] = "EAST";
	dirPriority1[2] = "NORTH";
	dirPriority1[1] = "WEST";

	dirPriorityInversorState[false] = dirPriority0;
	dirPriorityInversorState[true] = dirPriority1;
}


Case getCase(Case c, string direction, vector<vector<Case>> board ) {

	int ligne = c.ligne;
	int colonne = c.colonne;

	Case cas;
	if (direction == "SOUTH") {
		cas = board[ligne + 1][colonne];
	}
	if (direction == "EAST") {
		cas = board[ligne][colonne + 1];
	}

	if (direction == "NORTH") {
		cas = board[ligne - 1][colonne];
	}

	if (direction == "WEST") {
		cas = board[ligne][colonne-1];
	}
	return cas;
}

int main()
{
    int L;
    int C;
    cin >> L >> C; cin.ignore();
	vector<vector<Case>> board;
	//map<pair<int, int>, Case> board;
	Case currentCase;
    for (int i = 0; i < L; i++) {
        string row;
        getline(cin, row);
		vector<Case> ligneVec;
		for (int j = 0; j < row.length(); j++) {
			//pair<int, int> p = make_pair(j, i);
			Case c;
			c.element = row[j];
			c.ligne = i;
			c.colonne = j;
			if (c.element == '@') {
				currentCase = c;
			}
			ligneVec.push_back(c);
			//board[p] = c;
			//cerr << row[j];
		}
		board.push_back(ligneVec);
		//cerr << endl;
    }


	//debugBoard(C,L,board);
	map<char, string> letterDirection;
	initLetterDirection(letterDirection);
	map<bool, map<int, string>> dirPriorityInversorState;
	initDirPriority(dirPriorityInversorState);

	string direction="SOUTH";
	bool Casseur = false;
	bool inversorState = false;
	bool loop = false;
	vector<string> directionsToTake;
	int i = 1;
	Case nextCase;
	Case caseForLoop;
	bool analyzeLoop = false;

	while ( (currentCase.element!='$') && (!loop)) {

		// SI case deja visitée
		if (board[currentCase.ligne][currentCase.colonne].visited) {
			if (analyzeLoop) {
				if ((caseForLoop.ligne == currentCase.ligne) && (caseForLoop.colonne == currentCase.colonne)) {
					loop = true;
				}
			}
			else {
				caseForLoop = currentCase;
				analyzeLoop = true;
			}
		}
		else {
			analyzeLoop = false;
		}

		board[currentCase.ligne][currentCase.colonne].visited = true;
		char c = currentCase.element;

		if (c == 'B') {
			Casseur = !Casseur;
		}

		if (c == 'I') {
			inversorState = !inversorState;
		}

		if (c == 'E' || c == 'S' || c == 'N' || c == 'W') {
			direction = letterDirection[c];
			nextCase = getCase(currentCase, direction, board);
		}

		nextCase = getCase(currentCase, direction, board);
		//cerr << direction << " " << nextCase.element << endl;
		if ((nextCase.element == 'X' && !Casseur)  || (nextCase.element=='#')) { // Obstacle bloquant
			int priority = 1;
			while ((nextCase.element == 'X' && !Casseur) || (nextCase.element == '#')) {
				direction = dirPriorityInversorState[inversorState][priority];
				nextCase = getCase(currentCase, direction, board);
				priority++;
			}

		}

		if (nextCase.element == 'X' && Casseur) {
			board[nextCase.ligne][nextCase.colonne].element = ' ';
		}
		

		if (nextCase.element == 'T') {
			//cerr << "==T" << endl;
			bool found = false;
			int i = 0;
			while ((i<L) && (!found)) {
				int j = 0;
				while ((j<C) && (!found)) {
					Case c = board[i][j];
					//cerr << c.element << " , " << c.ligne << " / " << nextCase.ligne << " - " << c.colonne << " / " << nextCase.colonne << endl;
					if ( (c.element == 'T') && ((c.ligne!=nextCase.ligne) || (c.colonne!=nextCase.colonne))) {
						//cerr << "Teleporteur : " << i << " / " << j << endl;
						nextCase = board[i][j];
						found = true;
					}
						j++;
				}
				i++;
			}
		}

		currentCase = nextCase;
		//cerr << i<<", direction : "<< direction << endl;
		//cerr << " nextCase , element : " << nextCase.element << endl;
		directionsToTake.push_back(direction);
	}

	if (!loop) {
		for (int i = 0; i < directionsToTake.size(); i++) {
			cout << directionsToTake[i] << endl;
		}

	}
	else {
		cout << "LOOP" << endl;
	}


    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

   
}