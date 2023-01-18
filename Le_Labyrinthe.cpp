#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <utility>
#include <stack>

using namespace std;

int width;
int height;

struct Square {
	vector<string> dirAllowed;
	vector<string> neighborsDir;
	map<string, pair<int, int>> neighbors;
	bool seen;
	bool walkable = false;
	string directionToWin = "";
	int x;
	int y;
};


bool sameSquareCoord(int x1, int y1, int x2, int y2) {
	return ((x1 == x2) && (y1 == y2));
}


string getOppositeDirection(string direction) {

	if (direction == "LEFT") {
		return "RIGHT";
	}
	if (direction == "RIGHT") {
		return "LEFT";
	}
	if (direction == "UP") {
		return "DOWN";
	}
	if (direction == "DOWN") {
		return "UP";
	}
	return "";
}

void resetBoard(vector<Square> board[]) {

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			board[i][j].seen = false;
			board[i][j].directionToWin = "";
		}
	}
}

void debugPath(vector<string> path) {
	for (int j = 0; j < path.size(); j++) {
		cerr << path[j] << endl;
	}
}

void debugSquare(Square s) {

	for (int j = 0; j < s.dirAllowed.size(); j++) {
		cerr << s.dirAllowed[j] << endl;
	}
}


void debugBoard(vector<Square> board[]) {
	for (int i = 0; i < height; i++) {// HEIGHT
		for (int j = 0; j < width; j++) {// COLUMN
			Square s = board[i][j];
			if (s.walkable) {
			cerr<<"w";
			}
			else {
			cerr << "x";
			}
		}
		cerr << endl;
	}
}

bool isWalkable(char c) {
	return ((c == '.') || (c == 'T') || (c == 'C'));
}


void initBoard(vector<Square> board[]) {
	int x, y;
	//cerr << width << " " << height << endl;
	for (int i = 0; i < height; i++) {
		vector<Square> vec;
		for (int j = 0; j < width; j++) {
			struct Square currentSquare;
			currentSquare.seen = false;
			currentSquare.x = j;
			currentSquare.y = i;
			// voisin gauche
			x = j - 1;
			y = i;
			if (x >= 0) {
				currentSquare.neighborsDir.push_back("LEFT");
				currentSquare.neighbors["LEFT"] = make_pair(y, x);
			}
			// voisin droite
			x = j + 1;
			y = i;
			if (x < width) {
				currentSquare.neighborsDir.push_back("RIGHT");
				currentSquare.neighbors["RIGHT"] = make_pair(y, x);
			}
			// voisin haut
			x = j;
			y = i - 1;
			if (y >= 0) {
				currentSquare.neighborsDir.push_back("UP");
				currentSquare.neighbors["UP"] = make_pair(y, x);
			}
			// voisin bas
			x = j;
			y = i + 1;
			if (y < height) {
				currentSquare.neighborsDir.push_back("DOWN");
				currentSquare.neighbors["DOWN"] = make_pair(y, x);
			}
			vec.push_back(currentSquare);
		}
		board[i] = vec;
	}
}

void initSquareCheck(vector<bool> squareCheck[]) {

	for (int i = 0; i < height; i++) {
		vector<bool> vec;
		for (int j = 0; j < width; j++) {
			vec.push_back(false);
		}
		squareCheck[i] = vec;
	}
}

vector<string> getVectorFromPath(vector<Square> board[], int ystart, int xstart) {

	vector<string> path;
	Square currentSquare = board[ystart][xstart];
	string dir = currentSquare.directionToWin;
	while (dir != "") {
		path.push_back(dir);
		pair<int, int> coord = currentSquare.neighbors[dir];
		currentSquare = board[coord.first][coord.second];
		dir = currentSquare.directionToWin;
	}

	return path;
}

bool isPathAllowed(vector<Square> board[], vector<string> path, int x, int y) {

	int i = 0;
	bool ok = true;
	Square square = board[y][x];
	while ((i < path.size()) && (ok)) {
		int j = 0;
		vector<string> vec = square.dirAllowed;
		string dir = "";
		if (!vec.empty()) {
			dir = vec[j];
		}
		while ((j<vec.size()) && (dir != path[i])) {
			j++;
		}
		if (j == vec.size()) {
			ok = false;
		}
		else {
			pair<int, int> coord = square.neighbors[path[i]];
			square = board[coord.first][coord.second];
		}
		i++;
	}

	return ok;
}

bool getPath(vector<Square> board[], int ystart, int xstart, int yfinish, int xfinish) {
	queue<pair<int, int>> coordQueue;
	pair<int, int> finishCoord = make_pair(yfinish, xfinish);
	coordQueue.push(finishCoord);
	pair<int, int> currentCoord = coordQueue.front();
	bool finish = false;

	//cerr << "SOURCE" << endl;
	//cerr << currentCoord.second << " / " << currentCoord.first << endl;

	finish = sameSquareCoord(ystart, xstart, currentCoord.first, currentCoord.second);
	while ((!coordQueue.empty()) && (!finish)) {
		//cerr << currentCoord.second << " / " << currentCoord.first<< endl;
		coordQueue.pop();
		Square currentSquare = board[currentCoord.first][currentCoord.second];
		board[currentCoord.first][currentCoord.second].seen = true;
		int taille = currentSquare.dirAllowed.size();
		//cerr << "VOISINS" << endl;
		int i = 0;
		while ((i < taille) && (!finish)) {

			string dir = currentSquare.dirAllowed[i];
			pair<int, int> neighborCoord = currentSquare.neighbors[dir];
			Square neighbor = board[neighborCoord.first][neighborCoord.second];
			//board[neighborCoord.first][neighborCoord.second].directionToWin = getOppositeDirection(dir);
			finish = sameSquareCoord(ystart, xstart, neighborCoord.first, neighborCoord.second);
			if (!neighbor.seen) {

				coordQueue.push(neighborCoord);
				string oppositeDir = getOppositeDirection(dir);
				//cerr << neighborCoord.second << " / " << neighborCoord.first <<" / " <<oppositeDir<<endl;
				board[neighborCoord.first][neighborCoord.second].directionToWin = oppositeDir;
				board[neighborCoord.first][neighborCoord.second].seen = true;
			}
			i++;
		}
		currentCoord = (!coordQueue.empty() || !finish) ? coordQueue.front() : make_pair(0, 0);
		/*if (yfinish == 5) {
		cerr << "SOURCE" << endl;
		cerr << currentCoord.first << " / " << currentCoord.second << endl;
		}*/

	}
	return finish;
}

void eraseDir(vector<Square> board[], int y, int x, string direction) {

	//cerr << "ERASE " << x << " / " << y << " / " << direction << endl;

	vector<string> dirAllowed = board[y][x].dirAllowed;
	int i = 0;
	if (!dirAllowed.empty()) {
		while ((i < dirAllowed.size()) && (dirAllowed[i] != direction)) {
			i++;
		}
		//cerr << i << endl;
		if (i<dirAllowed.size()) {
			board[y][x].dirAllowed.erase(board[y][x].dirAllowed.begin() + i);
			//board[x][y].neighbors.erase(direction);
		}
	}

}

void UpdateBoard(vector<Square> board[], int y, int x, bool walkable) {

	Square s = board[y][x];
	vector<string> nDir = s.neighborsDir;
	map<string, pair<int, int>> neighbors=s.neighbors;
	//cerr << "Update Board " << x << " , " << y << " " << walkable << endl;
	if (walkable) {
		for (int i = 0; i < nDir.size(); i++) {
			string dir = nDir[i];
			//cerr << dir << endl;
			pair<int, int> nCoord = neighbors[dir];
			string dirOpp = getOppositeDirection(dir);
			//cerr << nCoord.second << " , " << nCoord.first << " / " << dirOpp << endl;
			board[nCoord.first][nCoord.second].dirAllowed.push_back(dirOpp);
		}
	}
	else {
		for (int i = 0; i < nDir.size(); i++) {
			string dir = nDir[i];
			pair<int, int> nCoord = neighbors[dir];
			eraseDir(board,nCoord.first,nCoord.second,getOppositeDirection(dir));
		}
	}
	board[y][x].walkable = walkable;
}


void getDirPriorities(map<int, string>& dirPriorities, int meY, int meX, int y, int x) {


	if ((x > meX) && (y > meY)) {
		cerr << "1" << endl;
		dirPriorities[0] = "DOWN";
		dirPriorities[1] = "RIGHT";
		dirPriorities[2] = "UP";
		dirPriorities[3] = "LEFT";
	}
	if ((x > meX) && (y < meY)) {
		cerr << "2" << endl;
		dirPriorities[0] = "UP";
		dirPriorities[1] = "RIGHT";
		dirPriorities[2] = "DOWN";
		dirPriorities[3] = "LEFT";
	}
	if ((x < meX) && (y > meY)) {
		cerr << "3" << endl;
		dirPriorities[0] = "DOWN";
		dirPriorities[1] = "LEFT";
		dirPriorities[2] = "UP";
		dirPriorities[3] = "RIGHT";
	}
	if ((x < meX) && (y < meY)) {
		cerr << "4" << endl;
		dirPriorities[0] = "UP";
		dirPriorities[1] = "LEFT";
		dirPriorities[2] = "DOWN";
		dirPriorities[3] = "RIGHT";
	}

	if ((x == meX) && (y > meY)) {
		cerr << "5" << endl;
		dirPriorities[0] = "DOWN";
		dirPriorities[1] = "RIGHT";
		dirPriorities[2] = "LEFT";
		dirPriorities[3] = "UP";
	}
	if ((x == meX) && (y < meY)) {
		cerr << "6" << endl;
		dirPriorities[0] = "UP";
		dirPriorities[1] = "RIGHT";
		dirPriorities[2] = "LEFT";
		dirPriorities[3] = "DOWN";
	}
	if ((x > meX) && (y == meY)) {
		cerr << "7" << endl;
		dirPriorities[0] = "RIGHT";
		dirPriorities[1] = "DOWN";
		dirPriorities[2] = "UP";
		dirPriorities[3] = "LEFT";
	}
	if ((x < meX) && (y == meY)) {
		cerr << "8" << endl;
		dirPriorities[0] = "LEFT";
		dirPriorities[1] = "DOWN";
		dirPriorities[2] = "UP";
		dirPriorities[3] = "LEFT";
	}

}





int main()
{
    int R; // number of rows.
    int C; // number of columns.
    int A; // number of rounds between the time the alarm countdown is activated and the time the alarm goes off.
    cin >> R >> C >> A; cin.ignore();

	width = C;
	height = R;
	vector<Square> board[height];
	initBoard(board);
	Square CommandRoom;
	Square startRoom;
	Square currentSquare;
	bool begin = true;
	bool commandFound = false;
	int state = 0;
	vector<string> path;
	vector<string> path2;
	vector<string> blindpath;
	map<int, string> dirPriorities;
	int dirPriority = 0;
	int centerX = C / 2;
	int centerY = R / 2;


	vector<bool> squareCheck[height];
	initSquareCheck(squareCheck);
	stack<Square> squareStack;
    // game loop
    while (1) {
        int KR; // row where Kirk is located.
        int KC; // column where Kirk is located.
        cin >> KR >> KC; cin.ignore();
		currentSquare = board[KR][KC];
		if (begin) {
			startRoom = board[KR][KC];
			begin = false;
		}
        for (int i = 0; i < R; i++) {// HEIGHT
            string ROW; // C of the characters in '#.TC?' (i.e. one line of the ASCII maze).
            cin >> ROW; cin.ignore();
			for (int j = 0; j < ROW.length(); j++) {// COLUMN
				char c = ROW[j];
				Square s = board[i][j];
				bool b = isWalkable(c);
				if (b != s.walkable) {
					UpdateBoard(board, i, j, b);
				}
				if(  (!commandFound ) && (c == 'C') ) {
					CommandRoom=board[i][j];
					commandFound = true;
				}
				//cerr << c;
			}
			//cerr << endl;
        }

		string way = "";

		/*string dir = "DOWN";
		currentSquare = board[6][5];
		pair<int, int> nCoord = currentSquare.neighbors[dir];
		Square neighbor = board[nCoord.first][nCoord.second];
		cerr << neighbor.x << " " << neighbor.y << " / walkable : "<< neighbor.walkable<< endl;*/

		//cerr << "DEBUG SQUARE" << endl;
		//debugSquare(currentSquare);

		//cerr << "commandFound : " << commandFound << endl;
		//dirPriority = 0;

		if (state == 0) { // Cherche un chemin vers la salle de commande

			if (commandFound) {
				bool inCommandRoom = sameSquareCoord(KR, KC, CommandRoom.y, CommandRoom.x);
				if (inCommandRoom) {
					state = 2;
				}
				else {
					resetBoard(board);
					bool canAccessRoom = getPath(board, KR, KC, CommandRoom.y, CommandRoom.x);
					if (canAccessRoom) {
						path = getVectorFromPath(board, KR, KC);
						state = 1;
					}
					else {
						if (blindpath.empty()) {
							getDirPriorities(dirPriorities, KR, KC, CommandRoom.y, CommandRoom.x);
							vector<string> dirs;
							int x = 0;
							while (x < 4) {
								dirs.push_back(dirPriorities[dirPriority]);
								dirPriority=(dirPriority + 1) % 4;
								x++;
							}
							for (int i = dirs.size() - 1; i >= 0; i--) {
								squareCheck[currentSquare.y][currentSquare.x] = true;
								pair<int, int> nCoord = currentSquare.neighbors[dirs[i]];
								Square neighbor = board[nCoord.first][nCoord.second];
								bool w = neighbor.walkable;
								bool s = squareCheck[nCoord.first][nCoord.second];
								if ((w) && (!s)) {
									squareCheck[nCoord.first][nCoord.second] = true;
									squareStack.push(neighbor);
								}
							}
							Square squareToGo = squareStack.top();
							squareStack.pop();
							resetBoard(board);
							getPath(board, KR, KC, squareToGo.y, squareToGo.x);
							blindpath = getVectorFromPath(board, KR, KC);

						}
						way = blindpath[0];
						blindpath.erase(blindpath.begin());
					}
				}
				
			}
			else {
				if (blindpath.empty()) {
					getDirPriorities(dirPriorities, KR, KC, centerY, centerX);
					vector<string> dirs;
					int x = 0;
					//cerr << "avant "<<dirPriority << endl;
					while (x < 4) {
						dirs.push_back(dirPriorities[dirPriority]);
						dirPriority=(dirPriority + 1) % 4;
						x++;
					}
					//cerr << "apres " << dirPriority << endl;
					for (int i = dirs.size()-1; i >= 0; i--) {

						squareCheck[currentSquare.y][currentSquare.x] = true;
						pair<int, int> nCoord = currentSquare.neighbors[dirs[i]];
						Square neighbor = board[nCoord.first][nCoord.second];
						bool w = neighbor.walkable;
						bool s = squareCheck[nCoord.first][nCoord.second];
						if ((w) && (!s)) {
							squareCheck[nCoord.first][nCoord.second] = true;
							squareStack.push(neighbor);
						}
					}
					Square squareToGo = squareStack.top();
					squareStack.pop();
					resetBoard(board);
					bool canGo=getPath(board, KR, KC, squareToGo.y, squareToGo.x);
					blindpath = getVectorFromPath(board, KR, KC);
					//cerr << squareToGo.x << " " << squareToGo.y << " "<<canGo<< endl;
					//debugSquare(squareToGo);
				}
				way = blindpath[0];
				blindpath.erase(blindpath.begin());
			}

		}
		if (state == 1) { // Chemin vers la salle de commande

			bool inCommandRoom = sameSquareCoord(KR, KC, CommandRoom.y, CommandRoom.x);
			if (inCommandRoom) {
				state = 2;
			}
			else {
				way = path[0];
				path.erase(path.begin());
			}
			
		}
		if (state == 2) { // Chemin vers le point de depart
			if (path2.empty()) {
				resetBoard(board);
				bool canGoBack=getPath(board, KR, KC, startRoom.y, startRoom.x);
				cerr << "goback : " << canGoBack << endl;
				path2 = getVectorFromPath(board, KR, KC);
			}
			
			way = path2[0];
			//way = getOppositeDirection(way);
			path2.erase(path2.begin());
		}

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        cout << way << endl; // Kirk's next move (UP DOWN LEFT or RIGHT).
    }
}