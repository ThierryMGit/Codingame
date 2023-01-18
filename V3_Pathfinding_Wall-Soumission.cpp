#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <utility>
#include <queue>

using namespace std;


int width = 9;
int height = 9;


struct Square {
	vector<string> dirAllowed;
	map<string, pair<int, int>> neighbors;
	bool seen;
	string directionToWin = "";
};


struct Player {
	int x;
	int y;
	int nbWalls;
	int id;
	bool me = false;
	bool play = true;
	vector<string> path;
};


struct Wall{
	int x;
	int y;
	string orientation;
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

int testDistPath(vector<Player> players, int distance, int myId) {

	int i = 0;
	int idPlayer = -1;
	int dist;
	int distmin = 100;
	while (i < players.size()) {
		if (players[i].play) {
			dist = players[i].path.size();
			//cerr << i << " / " << dist << endl;
			if ((i != myId) && (dist< distance) && (dist < distmin)) {
				idPlayer = i;
				distmin = dist;
			}
		}
		i++;
	}
	return idPlayer;
}

bool isPathAllowed(vector<Square> board[],vector<string> path, int x, int y) {

	int i = 0;
	bool ok = true;
	Square square = board[x][y];
	while ((i < path.size()) && (ok)) {
		int j = 0;
		vector<string> vec = square.dirAllowed;
		string dir="";
		if (!vec.empty()) {
			dir = vec[j];
		}
		while ((j<vec.size()) && (dir!=path[i])) {
			j++;
		}
		if (j == vec.size()) {
			ok = false;
		}
		else {
			pair<int,int> coord= square.neighbors[path[i]];
			square = board[coord.first ][coord.second];
		}
		i++;
	}

	return ok;
}


bool isWallBlocking(vector<string> p, int playerX, int playerY) {

	bool ok = false;
	if(p.size())


	return ok;
}




void initBoard(vector<Square> board[]) {
	int x, y;
	for (int i = 0; i < width; i++) {
		vector<Square> vec;
		for (int j = 0; j < height; j++) {
			struct Square currentSquare;
			currentSquare.seen = false;
			// voisin gauche
			x = i - 1;
			y = j;
			if (x >= 0) {
				currentSquare.dirAllowed.push_back("LEFT");
				currentSquare.neighbors["LEFT"] = make_pair(x, y);
			}
			// voisin droite
			 x = i + 1;
			 y = j;
			if (x < width) {
				currentSquare.dirAllowed.push_back("RIGHT");
				currentSquare.neighbors["RIGHT"] = make_pair(x, y);
			}
			// voisin haut
			 x = i;
			 y = j - 1;
			if (y >= 0) {
				currentSquare.dirAllowed.push_back("UP");
				currentSquare.neighbors["UP"] = make_pair(x, y);
			}
			// voisin bas
			 x = i;
			 y = j + 1;
			if (y < height) {
				currentSquare.dirAllowed.push_back("DOWN");
				currentSquare.neighbors["DOWN"] = make_pair(x, y);
			}
			vec.push_back(currentSquare);
		}
		board[i] = vec;
	}
}


vector<string> getVectorFromPath(vector<Square> board[], int xstart, int ystart) {

	vector<string> path;
	Square currentSquare = board[xstart][ystart];
	string dir = currentSquare.directionToWin;
	while (dir != "") {
		path.push_back(dir);
		pair<int, int> coord = currentSquare.neighbors[dir];
		currentSquare = board[coord.first][coord.second];
		dir = currentSquare.directionToWin;
	}

return path;
}



bool getPath(vector<Square> board[], int xstart, int ystart, int xfinish, int yfinish) {
	queue<pair<int, int>> coordQueue;
	pair<int, int> finishCoord = make_pair(xfinish, yfinish);
	coordQueue.push(finishCoord);
	pair<int, int> currentCoord = coordQueue.front();
	bool finish = false;
	/*if (yfinish == 5) {


		cerr << "SOURCE" << endl;
		cerr << currentCoord.first << " / " << currentCoord.second << endl;
	}*/
	finish = sameSquareCoord(xstart, ystart, currentCoord.first, currentCoord.second);
	while ((!coordQueue.empty()) && (!finish)) {
		//cerr << currentCoord.first << " / " << currentCoord.second<< endl;
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
			finish = sameSquareCoord(xstart, ystart, neighborCoord.first, neighborCoord.second);
			if (!neighbor.seen) {

				coordQueue.push(neighborCoord);
				string oppositeDir = getOppositeDirection(dir);
				//cerr << neighborCoord.first << " / " << neighborCoord.second <<" / " <<oppositeDir<<endl;
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



vector<string> shortestPath(vector<Square> board[], int xstart, int ystart, int idPlayer, int index) {

	vector<string> path;
	if (idPlayer == 0) {
		if (getPath(board, xstart, ystart, width - 1, index)) {
			path = getVectorFromPath(board, xstart, ystart);
			path.push_back("RIGHT");
			//cerr << "finish en " << << "" << <<endl;
			//debugPath(path);
		}

	}
	if (idPlayer == 1) {
		if (getPath(board, xstart, ystart, 0, index)) {
			path = getVectorFromPath(board, xstart, ystart);
			path.push_back("LEFT");
		}
	}
	if (idPlayer == 2) {
		if (getPath(board, xstart, ystart, index, width - 1)) {
			path = getVectorFromPath(board, xstart, ystart);
			path.push_back("DOWN");
		}
	}
	return path;
}


vector<string> shortestPathParent(vector<Square> board[], int xstart, int ystart, int idPlayer) {
	//cerr << "shortestPathParent" << endl;
	vector<string> finalPath;
	vector<string> path;
	int pathlengthmin = 1000;
	int pathlength;
	for (int i = 0; i < width; i++) {
		resetBoard(board);
		//cerr << "index " << i << endl;
		path = shortestPath(board, xstart, ystart, idPlayer, i);
		pathlength = path.size();
		if ((pathlength > 0) && (pathlength < pathlengthmin)) {
			finalPath = path;
			pathlengthmin = pathlength;
		}
	}
	return finalPath;
}

void eraseDir(vector<Square> board[], int x, int y, string direction) {

	//cerr << "ERASE " << x << " / " << y << " / " << direction << endl;

	vector<string> dirAllowed = board[x][y].dirAllowed;
	int i = 0;
	if (!dirAllowed.empty()) {
		while ( (i < dirAllowed.size()) && (dirAllowed[i] != direction) ){
			i++;
		}
		//cerr << i << endl;
		if (i<dirAllowed.size()) {
			board[x][y].dirAllowed.erase(board[x][y].dirAllowed.begin() + i);
			board[x][y].neighbors.erase(direction);
		}
	}
	
}

bool testDir(vector<Square> board[], int x, int y, string direction) {

	//cerr << "ERASE " << x << " / " << y << " / " << direction << endl;
	bool ok = false;
	vector<string> dirAllowed = board[x][y].dirAllowed;
	int i = 0;
	if (!dirAllowed.empty()) {
		while ((i < dirAllowed.size()) && (dirAllowed[i] != direction)) {
			i++;
		}
		//cerr << i << endl;
		if (i<dirAllowed.size()) {
			ok = true;
		}
	}
	return ok;
}

bool isWallPlaceable(vector<Square> board[], int wallX, int wallY, string wallOrientation) {

	bool ok = false;
	if ( (wallX > 0 && wallX < width) && (wallY >= 0 && wallY < height) ) {
		if ((wallOrientation == "V") && (wallX > 0 && wallY < height - 1)) {

			// CASE TOP LEFT
			ok = testDir(board, wallX - 1, wallY, "RIGHT");

			if (ok) {
				// CASE BOTTOM LEFT
				ok = testDir(board, wallX - 1, wallY + 1, "RIGHT");
			}
			if (ok) {
				// CASE TOP RIGHT
				ok = testDir(board, wallX, wallY, "LEFT");
			}
			if (ok) {
				// CASE BOTTOM RIGHT
				ok = testDir(board, wallX, wallY + 1, "LEFT");
			}

			if (ok) {
				// CASE BETWEEN BOTTOM RIGHT AND TOP RIGHT
				ok = testDir(board, wallX, wallY, "DOWN");
			}
		}
		if ((wallOrientation == "H") && (wallX < width - 1 && wallY > 0)) {

			// CASE TOP LEFT
			ok = testDir(board, wallX, wallY - 1, "DOWN");

			if (ok) {
				// CASE TOP RIGHT
				ok = testDir(board, wallX + 1, wallY - 1, "DOWN");
			}
			if (ok) {
				// CASE BOTTOM LEFT
				ok = testDir(board, wallX, wallY, "UP");
			}
			if (ok) {
				// CASE BOTTOM RIGHT
				ok = testDir(board, wallX + 1, wallY, "UP");
			}
			if (ok) {
				// CASE CASE BETWEEN LEFT RIGHT AND BOTTOM RIGHT
				ok = testDir(board, wallX, wallY, "RIGHT");
			}
		}
	}
	return ok;
}

void placeWall(vector<Square> board[], int wallX, int wallY, string wallOrientation) {

	if (wallOrientation == "V") {

		// CASE TOP LEFT
		eraseDir(board, wallX - 1, wallY,"RIGHT");

		// CASE BOTTOM LEFT
		eraseDir(board, wallX - 1, wallY + 1,"RIGHT");

		// CASE TOP RIGHT
		eraseDir(board, wallX, wallY, "LEFT");

		// CASE BOTTOM RIGHT
		eraseDir(board, wallX, wallY + 1, "LEFT");
	}
	if (wallOrientation == "H") {

		// CASE TOP LEFT
		eraseDir(board, wallX, wallY - 1, "DOWN");

		// CASE TOP RIGHT
		eraseDir(board, wallX + 1, wallY - 1, "DOWN");

		// CASE BOTTOM LEFT
		eraseDir(board, wallX, wallY, "UP");

		// CASE BOTTOM RIGHT
		eraseDir(board, wallX + 1, wallY, "UP");
	}
}


vector<Wall> generateWalls(int x, int y, string direction) {

	vector<Wall> walls;
	if (direction == "RIGHT") {
		struct Wall wall1;
		wall1.orientation = "V";
		wall1.x = x + 1;
		wall1.y = y;

		struct Wall wall2;
		wall2.orientation = "V";
		wall2.x = x + 1;
		wall2.y = y - 1;

		walls.push_back(wall1);
		walls.push_back(wall2);
	}
	if (direction == "LEFT") {
		struct Wall wall1;
		wall1.orientation = "V";
		wall1.x = x;
		wall1.y = y;

		struct Wall wall2;
		wall2.orientation = "V";
		wall2.x = x;
		wall2.y = y - 1;

		walls.push_back(wall1);
		walls.push_back(wall2);
	}
	if (direction == "DOWN") {
		struct Wall wall1;
		wall1.orientation = "H";
		wall1.x = x;
		wall1.y = y + 1;

		struct Wall wall2;
		wall2.orientation = "H";
		wall2.x = x - 1;
		wall2.y = y + 1;

		walls.push_back(wall1);
		walls.push_back(wall2);
	}
	if (direction == "UP") {
		struct Wall wall1;
		wall1.orientation = "H";
		wall1.x = x;
		wall1.y = y - 1;

		struct Wall wall2;
		wall2.orientation = "H";
		wall2.x = x - 1;
		wall2.y = y - 1;

		walls.push_back(wall1);
		walls.push_back(wall2);
	}
	return walls;
}


/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
	int w; // width of the board
	int h; // height of the board
	int playerCount; // number of players (2,3, or 4)
	int myId; // id of my player (0 = 1st player, 1 = 2nd player, ...)
	cin >> w >> h >> playerCount >> myId; cin.ignore();

	vector<Square> board[height];
	initBoard(board);

	//pair<int, int> neighborCoord = board[0][0].neighbors["DOWN"];
	//cerr << neighborCoord.first << " / " << neighborCoord.second << endl;


	/*vector<string> path;
	//getPath(board, 4, 6, x, y);

	path = shortestPathParent(board, 4, 6, 2);
	for (int j = 0; j < path.size(); j++) {
		cerr << path[j] << endl;
	}*/


	//cerr << path.size() << endl;

	/*for (int i = 0; i < path.size(); i++) {
		cerr << path[i] << endl;
	}*/
	// test
	//shortestPathParent(board, 0, 0, myId);

	vector<Player> players;
	bool begin = true;

	// game loop
	while (1) {


		for (int i = 0; i < playerCount; i++) {
			int x; // x-coordinate of the player
			int y; // y-coordinate of the player
			int wallsLeft; // number of walls available for the player
			cin >> x >> y >> wallsLeft; cin.ignore();
			if (begin) {
				struct Player p;
				p.id = i;
				p.nbWalls = wallsLeft;
				p.x = x;
				p.y = y;
				if (i == myId) {
					p.me = true;
				}
				players.push_back(p);
			}
			else {
				players[i].nbWalls = wallsLeft;
				players[i].x = x;
				players[i].y = y;
			}

		}
		begin = false;
		int wallCount; // number of walls on the board
		cin >> wallCount; cin.ignore();
		for (int i = 0; i < wallCount; i++) {
			int wallX; // x-coordinate of the wall
			int wallY; // y-coordinate of the wall
			string wallOrientation; // wall orientation ('H' or 'V')
			cin >> wallX >> wallY >> wallOrientation; cin.ignore();
			placeWall(board, wallX, wallY, wallOrientation);
		}


		vector<int> pathDistances;
		int dist;
		for (int i = 0; i < playerCount; i++) {
			// recherche de chemin
			if (players[i].me) {
				// debug square
				//cerr << "SQUARE " << players[i].x <<" / " << players[i].y << endl;
				//debugSquare(board[players[i].x][players[i].y]);
				if ((!isPathAllowed(board, players[i].path, players[i].x, players[i].y)) || (players[i].path.empty())) {
					//cerr << "before shortest" << endl;
					players[i].path = shortestPathParent(board, players[i].x, players[i].y, players[i].id);
					dist = players[i].path.size();
					//cerr << "after shortest" << endl;
				}
				// debug
				//cerr << "P" << i << ", direction " << players[i].path[0] << endl;

			}
			else {
				if ( (players[i].x != -1) && (players[i].y != -1) &&  (players[i].nbWalls != -1) ){

					players[i].path = shortestPathParent(board, players[i].x, players[i].y, players[i].id);
					dist = players[i].path.size();
					// debug
					//cerr << "P" << i << ", direction " << players[i].path[0] << endl;
				}
				else {
					dist = -1;
					players[i].play = false;
				}
			}
			pathDistances.push_back(dist);
		}


		//**** Test si poser un mur ou faire son chemin

		string ordre;

		if (players[myId].nbWalls > 0) {

			// TEST POSER UN MUR POUR RALENTIR UN ADVERSAIRE
			int myDist = players[myId].path.size();
			int distanceToTest = myDist;
			int idJoueur = testDistPath(players, distanceToTest, myId);
			float moyDiffPath = 0F;


			if (idJoueur != -1) { // Un joueur est plus proche de la fin que moi ou est tout proche

				vector<Square> copyBoard[height];
				vector<Wall> walls = generateWalls(players[idJoueur].x, players[idJoueur].y, players[idJoueur].path[0]);
				int idWall = -1;
				float diffmax = 0;
				float pathdiff;
				float myDiff = 0;
				float diff = 0;

				for (int i = 0; i < walls.size(); i++) {
					Wall w = walls[i];
					if (isWallPlaceable(board, w.x, w.y, w.orientation)) {
						for (int j = 0; j < height; j++) {
							copyBoard[j] = board[j];
						}
						placeWall(copyBoard, w.x, w.y, w.orientation);

						// CONDITIONS DE PLACEMENT DU WALL
						pathdiff = 0;
						vector<string> p;
						bool isblocking = false;
						int nb = 0;
						int x = 0;
						while ((x < playerCount) && (!isblocking)) {

							if ((players[x].play) && (!players[x].me)) {
								nb++;
								p = shortestPathParent(copyBoard, players[x].x, players[x].y, players[x].id);
								pathdiff += pathDistances[x] - p.size();
								if (!isblocking) {
									isblocking = isPathAllowed(copyBoard, p, players[x].x, players[x].y);
								}

								//cerr << i << " " << p.size() << endl;
							}
							x++;
						}
						if (!isblocking) {
							bool isblockingme = false;
							p = shortestPathParent(copyBoard, players[myId].x, players[myId].y, players[myId].id);
							isblockingme = isPathAllowed(copyBoard, p, players[myId].x, players[myId].y);
							//(p.size() <= pathDistances[myId])
							pathdiff /= nb;
							myDiff = pathDistances[myId] - p.size();
							diff = myDiff - pathdiff;
							if ((diff > diffmax) && ( myDiff > pathdiff) && (myDiff < myDiffmin ) && (!isblockingme)) {
								idWall = i;
								pathDiffmax = pathdiff;
								diffmax = diff;
							}
						}
					}
				}

				if ((idWall == -1) || (pathDiffmax == 0)) {
					ordre = players[myId].path[0];
					players[myId].path.erase(players[myId].path.begin());
				}
				else {
					Wall w = walls[idWall];
					ordre = to_string(w.x) + " " + to_string(w.y) + " " + w.orientation;
				}

			}
		}
		else { // On continue notre chemin
			ordre = players[myId].path[0];
			players[myId].path.erase(players[myId].path.begin());
		}

		//pair<int, int> coord = board[myX][myY].neighbors[direction];
		//cerr << coord.first << " / " << coord.second << endl;

        cout << ordre << endl; // action: LEFT, RIGHT, UP, DOWN or "putX putY putOrientation" to place a wall
    }
}