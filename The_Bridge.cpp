#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <utility>


using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int width;
int height = 4;

struct Square {
	char c;
	int x;
	int y;
	bool walkable;
	vector<string> neighborsDir;
	map<string, pair<int, int>> neighbors;
};


struct Moto {
	int x;
	int y;
	int speed;
	bool working;
};


void debugBoard(vector<Square> board[],int xstart) {
	for (int i = 0; i < height; i++) {// HEIGHT
		for (int j = xstart; j < xstart +10; j++) {// COLUMN
			Square s = board[i][j];
			if (s.walkable) {
				cerr << "w";
			}
			else {
				cerr << "x";
			}
		}
		cerr << endl;
	}
}

void debugMotos(vector<Moto> m) {
	for (int i = 0; i < m.size(); i++) {
		cerr << m[i].x << " ," << m[i].y << " / " << m[i].speed << " ; " << m[i].working << endl;
	}
}

bool isWalkable(char c) {
	return (c == '.');
}

void getNeighbors(Square& s) {

	int x, y;
	// voisin gauche
	x = s.x - 1;
	y = s.y;
	if (x >= 0) {
		s.neighborsDir.push_back("LEFT");
		s.neighbors["LEFT"] = make_pair(y, x);
	}
	// voisin droite
	x = s.x + 1;
	y = s.y;
	if (x < width) {
		s.neighborsDir.push_back("RIGHT");
		s.neighbors["RIGHT"] = make_pair(y, x);
	}
	// voisin haut
	x = s.x;
	y = s.y - 1;
	if (y >= 0) {
		s.neighborsDir.push_back("UP");
		s.neighbors["UP"] = make_pair(y, x);
	}
	// voisin bas
	x = s.x;
	y = s.y + 1;
	if (y < height) {
		s.neighborsDir.push_back("DOWN");
		s.neighbors["DOWN"] = make_pair(y, x);
	}

}

void initChoices(vector<string>& choices) {
	choices.push_back("SPEED");
	choices.push_back("JUMP");
	choices.push_back("UP");
	choices.push_back("DOWN");
	choices.push_back("WAIT");
	choices.push_back("SLOW");
}

void resetMotos(vector<Moto>& copyMotos, vector<Moto> motos) {
	for (int i = 0; i < copyMotos.size(); i++) {
		copyMotos[i] = motos[i];
	}
}

int getnbMotosWork(vector<Moto> copyMotos) {

	int cpt = 0;
	for (int i = 0; i < copyMotos.size(); i++) {
		//cerr <<"working : " <<copyMotos[i].working << endl;
		if (copyMotos[i].working) {
			cpt++;
		}
		//cerr << "cpt : "<<cpt << endl;
	}
	return cpt;
}



void evalMotos(vector<Moto>& copyMotos, vector<Square> board[], string choice) {

	map<int, vector<Square>> SquareTocheck;
	int xmin, xmax,y;



	for (int i = 0; i < copyMotos.size(); i++) {

		Moto m = copyMotos[i];

		if (m.working) {
			if (choice == "SPEED") {
				copyMotos[i].speed = m.speed == 50 ? m.speed : m.speed + 1;
				xmin = m.x;
				xmax = m.x + copyMotos[i].speed >= (width-1) ? (width-1) : m.x + copyMotos[i].speed;

				for (int j = xmin; j <= xmax; j++) {
					//cerr << j << " " << y << endl;
					SquareTocheck[i].push_back(board[m.y][j]);
				}
				copyMotos[i].x = xmax;
			}
			if (choice == "SLOW") {
				copyMotos[i].speed = (m.speed - 1) < 1 ? 1 : m.speed - 1;
				xmin = m.x;
				xmax = m.x + copyMotos[i].speed >= (width-1) ? (width-1) : m.x + copyMotos[i].speed;
				for (int j = xmin; j <= xmax; j++) {
					SquareTocheck[i].push_back(board[m.y][j]);
				}
				copyMotos[i].x = xmax;
			}
			if (choice == "JUMP") {
				copyMotos[i].x = m.x + m.speed >= (width-1) ? (width-1) : m.x + m.speed;
				SquareTocheck[i].push_back(board[m.y][copyMotos[i].x]);
			}
			if (choice == "WAIT") {
				
				xmin = m.x;
				xmax = m.x + copyMotos[i].speed >= (width-1) ? (width-1) : m.x + copyMotos[i].speed;
				for (int j = xmin; j <= xmax; j++) {
					SquareTocheck[i].push_back(board[m.y][j]);
				}
				copyMotos[i].x = xmax;
			}
			if (choice == "UP") {
				if (m.speed != 0) {
					int LaneSpeed = m.speed;
					y = (m.y - 1) < 0 ? 0 : (m.y - 1);
					xmin = m.x;
					xmax = m.x + LaneSpeed >= (width-1) ? (width-1) : m.x + LaneSpeed;
					copyMotos[i].x = xmax;
					copyMotos[i].y = y;
					
					for (int j = xmin; j <= xmax; j++) {
						//cerr << j << " " << y << endl;
						SquareTocheck[i].push_back(board[y][j]);
					}

					if (y != m.y) {
						LaneSpeed = (m.speed - 1) < 1 ? 1 : m.speed - 1;
						y = m.y;
						xmin = m.x;
						xmax = m.x + LaneSpeed >= (width-1) ? (width-1) : m.x + LaneSpeed;
						for (int j = xmin; j <= xmax; j++) {
							//cerr << j << " " << y << endl;
							SquareTocheck[i].push_back(board[y][j]);
						}
					}
				}
				
			}
			if (choice == "DOWN") {
				if (m.speed != 0) {
					int LaneSpeed = m.speed;
					y = (m.y + 1) > 3 ? 3 : (m.y + 1);
					xmin = m.x;
					xmax = m.x + LaneSpeed >= (width-1) ? (width-1) : m.x + LaneSpeed;
					copyMotos[i].x = xmax;
					copyMotos[i].y = y;
					for (int j = xmin; j <= xmax; j++) {
						//cerr << j << " , " << y << endl;// " / " << board[y][j].x << " , " << board[y][j].y << endl;
						SquareTocheck[i].push_back(board[y][j]);
					}

					if (y != m.y) {
						LaneSpeed = (m.speed - 1) < 1 ? 1 : m.speed - 1;
						y = m.y;
						xmin = m.x;
						xmax = m.x + LaneSpeed >= (width-1) ? (width-1) : m.x + LaneSpeed;
						for (int j = xmin; j <= xmax; j++) {
							//cerr << j << " " << y << endl;
							SquareTocheck[i].push_back(board[y][j]);
						}
					}
				}
				
			}
		}
		
	}

	// Check Holes

	//cerr << "Check Holes" << endl;

	for (int i = 0; i < copyMotos.size(); i++) {
		vector<Square> s = SquareTocheck[i];
		int j = 0;
		bool walkable = true;
		//cerr <<" taille de check : " <<s.size() << endl;
		while ((j<s.size()) && (walkable)) {
			//cerr << s[j].x << " " << s[j].y << " " << s[j].walkable << endl;
			walkable = s[j].walkable;
			j++;
		}
		

		if (!walkable) {
			//cerr << "walkable : " << walkable << endl;
			copyMotos[i].working = false;
		}

	}


	// Other fail conditions






}


int getCptMoto(vector<Moto> copyMotos, vector<string> choices, vector<Square> board[], int nbAnticipate, int nbMotosToWork) {

	int cptMotoMax = 0;
	//debugMotos(copyMotos);
	int nbMotosWork = getnbMotosWork(copyMotos);

	if ( (nbAnticipate == 0) || (nbMotosWork < nbMotosToWork) ) {
		return nbMotosWork;
	}
	else {

		vector<Moto> copyMotos2;
		for (int i = 0; i < copyMotos.size(); i++) {
			copyMotos2.push_back(copyMotos[i]);
		}

		for (int i = 0; i < choices.size(); i++) {
			string choice = choices[i];
			//cerr << choice << endl;		
			evalMotos(copyMotos2, board, choice);
			//debugMotos(copyMotos);
			int cptMoto = getCptMoto(copyMotos2,choices, board, nbAnticipate -1, nbMotosToWork);
			//cerr << "cptmoto : " << cptMoto << endl;
			cptMotoMax = max(cptMoto, cptMotoMax);
			//debugMotos(copyMotos);
			resetMotos(copyMotos2, copyMotos);
			//debugMotos(copyMotos);
		}


	}

	return cptMotoMax;
}

int main()
{

	
	vector<Square> board[4];
	vector<Square> squares;

	int y = 0;

    int M; // the amount of motorbikes to control
    cin >> M; cin.ignore();
	vector<Moto> motos;
	vector<Moto> copyMotos;
    int V; // the minimum amount of motorbikes that must survive
    cin >> V; cin.ignore();
    string L0; // L0 to L3 are lanes of the road. A dot character . represents a safe space, a zero 0 represents a hole in the road.
    cin >> L0; cin.ignore();
	width = L0.length();
	for (int i = 0; i <width; i++) {
		char c = L0[i];
		Square s;
		s.c = c;
		s.x = i;
		s.y = y;
		s.walkable = isWalkable(c);
		getNeighbors(s);
		squares.push_back(s);
	}
	board[y] = squares;

    string L1;
    cin >> L1; cin.ignore();
	y++;
	for (int i = 0; i <width; i++) {
		char c = L1[i];
		Square s;
		s.c = c;
		s.x = i;
		s.y = y;
		s.walkable = isWalkable(c);
		getNeighbors(s);
		squares[i] = s;
	}
	board[y] = squares;
    string L2;
    cin >> L2; cin.ignore();
	y++;
	for (int i = 0; i <width; i++) {
		char c = L2[i];
		Square s;
		s.c = c;
		s.x = i;
		s.y = y;
		s.walkable = isWalkable(c);
		getNeighbors(s);
		squares[i] = s;
	}
	board[y] = squares;
    string L3;
    cin >> L3; cin.ignore();
	y++;
	for (int i = 0; i <width; i++) {
		char c = L3[i];
		Square s;
		s.c = c;
		s.x = i;
		s.y = y;
		s.walkable = isWalkable(c);
		getNeighbors(s);
		squares[i] = s;
	}
	board[y] = squares;


	//int xstart = 0;
	//debugBoard(board,xstart);

	vector<string> choices;
	initChoices(choices);
	//cerr << choices.size() << endl;

	bool begin = true;

    // game loop
    while (1) {
        int S; // the motorbikes' speed
        cin >> S; cin.ignore();
        for (int i = 0; i < M; i++) {
            int X; // x coordinate of the motorbike
            int Y; // y coordinate of the motorbike
            int A; // indicates whether the motorbike is activated "1" or detroyed "0"
            cin >> X >> Y >> A; cin.ignore();
			if (begin) {
				Moto m;
				m.x = X;
				m.y = Y;
				m.speed = S;
				m.working = A;
				motos.push_back(m);
				copyMotos.push_back(m);
			}
			else {
				motos[i].x = X;
				motos[i].y = Y;
				motos[i].speed = S;
				motos[i].working = A;

				copyMotos[i].x = X;
				copyMotos[i].y = Y;
				copyMotos[i].speed = S;
				copyMotos[i].working = A;
			}
        }

		//cerr << copyMotos.size() << endl;

		begin = false;
		string instruction = "";
		int cptMotoMax = 0;
		int nbAnticipate = 3;
		for (int i = 0; i < choices.size(); i++) {
			string choice = choices[i];
			//cerr << choice << endl;
			//debugMotos(copyMotos);
			evalMotos(copyMotos, board,choice);
			//debugMotos(copyMotos);
			int cptMoto = getCptMoto(copyMotos, choices, board, nbAnticipate,V);
			//cerr << "cptmoto : " << cptMoto << endl;
			if (cptMoto > cptMotoMax) {
				cptMotoMax = cptMoto;
				instruction = choice;
			}
			//debugMotos(copyMotos);
			resetMotos(copyMotos, motos);
			//debugMotos(copyMotos);
		}


        // A single line containing one of 6 keywords: SPEED, SLOW, JUMP, WAIT, UP, DOWN.
        cout << instruction << endl;
    }
}