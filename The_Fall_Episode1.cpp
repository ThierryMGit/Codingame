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

struct piece {
	map<string,string> entreesSorties;
};


void initPieces(vector<piece>& pieces) {

	
	for (int i = 0; i < 14; i++) {
		struct piece p;
		switch (i) {

		case 0:
			
			pieces.push_back(p);
			break;
		case 1:
			p.entreesSorties["LEFT"] = "BOTTOM";
			p.entreesSorties["RIGHT"] = "BOTTOM";
			p.entreesSorties["TOP"] = "BOTTOM";
			pieces.push_back(p);
			break;
		case 2:
			p.entreesSorties["LEFT"] = "RIGHT";
			p.entreesSorties["RIGHT"] = "LEFT";
			pieces.push_back(p);
			break;
		case 3:
			p.entreesSorties["TOP"] = "BOTTOM";
			pieces.push_back(p);
			break;
		case 4:
			p.entreesSorties["TOP"] = "LEFT";
			p.entreesSorties["RIGHT"] = "BOTTOM";
			pieces.push_back(p);
			break;
		case 5:
			p.entreesSorties["TOP"] = "RIGHT";
			p.entreesSorties["LEFT"] = "BOTTOM";
			pieces.push_back(p);
			break;
		case 6:
			p.entreesSorties["LEFT"] = "RIGHT";
			p.entreesSorties["RIGHT"] = "LEFT";
			pieces.push_back(p);
			break;
		case 7:
			p.entreesSorties["RIGHT"] = "BOTTOM";
			p.entreesSorties["TOP"] = "BOTTOM";
			pieces.push_back(p);
			break;
		case 8:
			p.entreesSorties["LEFT"] = "BOTTOM";
			p.entreesSorties["RIGHT"] = "BOTTOM";
			pieces.push_back(p);
			break;
		case 9:
			p.entreesSorties["LEFT"] = "BOTTOM";
			p.entreesSorties["TOP"] = "BOTTOM";
			pieces.push_back(p);
			break;
		case 10:
			p.entreesSorties["TOP"] = "LEFT";
			pieces.push_back(p);
			break;
		case 11:
			p.entreesSorties["TOP"] = "RIGHT";
			pieces.push_back(p);
			break;
		case 12:
			p.entreesSorties["RIGHT"] = "BOTTOM";
			pieces.push_back(p);
			break;
		case 13:
			p.entreesSorties["LEFT"] = "BOTTOM";
			pieces.push_back(p);
			break;
		default:
			break;
		}
	}
}

void getIntFromLine(string LINE, vector<int>& v) {

	int x;
	int begin = 0;
	bool newWord = true;
	//cerr << " ****  " << endl;
	while (x < LINE.length()) {
		//cerr << LINE[x] << endl;
		if ( (LINE[x] != ' ') && (newWord) ) {
			begin = x;
			newWord = false;
		}
		if (LINE[x] == ' ') {
			//cerr << "vide" << endl;
			//cerr << begin << " / " << LINE[begin] << endl;
			newWord = true;
			string s = LINE;
			string t = s.substr(begin, (x - begin));
			//cerr << t << endl;
			v.push_back(stoi(t));
		}

		x++;
		
	}

	v.push_back(stoi(LINE.substr(begin)));
	/*cerr << "debug vec" << endl;
	for (int i = 0; i < v.size(); i++) {
		cerr << v[i] << endl;
	}*/
}


void debugBoard(vector<int> board[], int H) {

	for (int i = 0; i < H; i++) {

		for (int j = 0; j < board[i].size(); j++) {

			cerr << board[i][j] << " | ";
		}
		cerr << endl;
	}


}

pair<int, int> getCoord(int x, int y,string dir) {
	pair<int, int> coord;
	int myX = x;
	int myY=y;
	if (dir == "UP"){
		myY = y - 1;
	}
	if (dir == "BOTTOM"){
		myY = y + 1;
	}
	if (dir == "LEFT"){
		myX = x - 1;
	}
	if (dir == "RIGHT"){
		myX = x + 1;
	}
	coord = make_pair(myX, myY);
	return coord;
}

int main()
{
	vector<piece> pieces;
	initPieces(pieces);

    int W; // number of columns.
    int H; // number of rows.
    cin >> W >> H; cin.ignore();

	vector<int> board[H];
    for (int i = 0; i < H; i++) {
        string LINE; // represents a line in the grid and contains W integers. Each integer represents one room of a given type.
        getline(cin, LINE);
		vector<int> v;
		//cerr << LINE << endl;
		getIntFromLine(LINE, v);
		board[i] = v;
    }
    int EX; // the coordinate along the X axis of the exit (not useful for this first mission, but must be read).
    cin >> EX; cin.ignore();

    // game loop
    while (1) {
        int XI;
        int YI;
        string POS;
        cin >> XI >> YI >> POS; cin.ignore();
		
		//debugBoard(board,H);


		string direction = pieces[board[YI][XI]].entreesSorties[POS];
		pair<int, int> coord = getCoord(XI,YI,direction);

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;


        // One line containing the X Y coordinates of the room in which you believe Indy will be on the next turn.
		cout << coord.first << " " <<coord.second << endl;
    }
}