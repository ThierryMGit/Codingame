#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <utility>
#include <string>
#include <math.h>
#include <ctime>

using namespace std;


#define PI 3.14159265

int KILL_SCORE = 10;
int DATA_SCORE = 100;



int XMIN = 0;
int YMIN = 0;
int XMAX = 16000;
int YMAX = 9000;



enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};



/**
 * Shoot enemies before they collect all the incriminating data!
 * The closer you are to an enemy, the more damage you do but don't get too close or you'll get killed.
 **/

struct data {
	int id;
	pair<float, float> coord;
	bool exist = false;
};


string displayCoord(pair<float, float> coord) {
	return to_string(coord.first) + " / " + to_string(coord.second);
}

float distance(pair<float, float> coord1, pair<float, float> coord2) {
	return sqrt(pow((coord2.first - coord1.first), 2) + pow((coord2.second - coord1.second), 2));
}

//float distance(pair<float, float> coord1, pair<int, int> coord2) {
//	return sqrt(pow((coord2.first - coord1.first), 2) + pow((coord2.second - coord1.second), 2));
//}

float vectorLength(pair<float, float> vec) {
	return sqrt(pow((vec.first), 2) + pow((vec.second), 2));
}

pair<float, float> vecCoord(pair<float, float> coord1, pair<float, float> coord2) {

	float x, y;
	x = coord2.first - coord1.first;
	y = coord2.second - coord1.second;
	return make_pair(x, y);
}

void normalizeVec(pair<float, float>& vec, float length) {
	vec.first = vec.first / length;
	vec.second = vec.second / length;
	//cerr << vec.first << " / " << vec.second << endl;
}

pair<float, float> nextLocation(pair<float, float>& vec, float vecLength, float distanceMax) {
	normalizeVec(vec,vecLength);
	float x = vec.first * distanceMax;
	float y = vec.second * distanceMax;
	return make_pair(x,y);
}

int computeScore(int DP, int L, int S, int EK) {
	return (DP*max(0, (L - 3 * S)) * 3) + DP * DATA_SCORE + EK * KILL_SCORE;
}


class Entity {

public:
	// constructeurs
	Entity();
	Entity(float distperturn);
	Entity(float distperturn, float x, float y);

	//destructeur
	virtual ~Entity();

	// attributs
	float distPerTurn;
	int idTarget;
	bool exist;
	pair<float, float> currentCoord;
	pair<int, int> nextCoord;
	pair<float, float> destination;
	pair<int, int> nextCoordTemp;

	// méthodes
	void setCurrentCoord(float x, float y);
	void setNextCoord(int x, int y);
	void setNextCoordTemp(int x, int y);
	void setDestination(float x, float y);

	pair<int, int> evaluateNextCoord(pair<float, float> from, pair<float, float> target);
	float distanceFromTarget(pair<float, float> from, pair<float, float> target);
	virtual int turnBeforeTarget(pair<float, float> from, pair<float, float> target, float fromDistance, bool data);


};

Entity::Entity() { exist = false; }
Entity::Entity(float distperturn) { distPerTurn = distperturn; exist = true; }
Entity::~Entity() {}
Entity::Entity(float distperturn, float x, float y) {
	distPerTurn = distperturn;
	currentCoord = make_pair(x, y);
	exist = true;
}
void Entity::setCurrentCoord(float x, float y) {
	currentCoord.first = x;
	currentCoord.second = y;
}
void Entity::setNextCoord(int x, int y) {
	nextCoord.first = x;
	nextCoord.second = y;
}
void Entity::setDestination(float x, float y) {
	destination.first = x;
	destination.second = y;
}
void Entity::setNextCoordTemp(int x, int y) {
	nextCoordTemp.first = x;
	nextCoordTemp.second = y;
}

float Entity::distanceFromTarget(pair<float, float> from, pair<float, float> target) {
	return distance(from, target);
}

//float Entity::distanceFromTarget2(pair<float, float> from, pair<float, float> target) {
//	
//}

pair<int, int> Entity::evaluateNextCoord(pair<float, float> from, pair<float, float> target) {
	pair<float,float> vec= vecCoord(from,target);
	float vecLength = vectorLength(vec);
	//cerr << displayCoord(from) <<" ! "<< displayCoord(target) << " !  "<<displayCoord(vec) << "! "<<vecLength<< endl;
	if (vecLength <= distPerTurn) {
		//cerr << "<=" << endl;
		return target;
	}
	else {
		//cerr << "else" << endl;
		pair<float,float> res=nextLocation(vec, vecLength,distPerTurn);
		pair<int, int> nextCo = make_pair((floor)(from.first + res.first), floor(from.second + res.second));
		return nextCo;
	}

	
}

int Entity::turnBeforeTarget(pair<float, float> from, pair<float, float> target, float fromDistance, bool data) {
	int turn = 0;
	float dist = distanceFromTarget(from, target);
	pair<float, float> coord = nextCoord;
	while (dist >= fromDistance) {
		turn++;
		coord = evaluateNextCoord(coord, target);
		dist = distanceFromTarget(coord, target);
	}
	return turn;
}





class Enemy : public Entity {


public:
	// constructeurs
	Enemy();
	Enemy(float distperturn, float x, float y, int id, int life);

	//destructeur
	~Enemy();

	// attributs
	int life;
	int id;
	int turnToTarget;
	int turnToTargetTemp;


	// méthodes
	void findDestination(map<int, struct data> datas);
	int turnBeforeTarget(pair<float, float> from, pair<float, float> target, float fromDistance, bool data);

};
Enemy::Enemy() { Entity(); turnToTarget = -1; }
Enemy::~Enemy() {}
Enemy::Enemy(float distperturn, float x, float y, int id, int life):Entity(distperturn, x, y) { this->life = life;  this->id = id; turnToTarget = -1; }
void Enemy::findDestination(map<int, struct data> datas) {

	float mindist = 999999;
	int idData = -1;
	map<int, struct data>::iterator it;
	for (it = datas.begin(); it != datas.end(); ++it) {
		float dist = distance(currentCoord, it->second.coord);
		if (dist < mindist) {
			mindist = dist;
			idData = it->second.id;
		}
		else if (dist == mindist) {
			idData = idData < it->second.id ? idData : it->second.id;
		}
	}

	idTarget = idData;
	setDestination(datas[idData].coord.first, datas[idData].coord.second);

}
int Enemy::turnBeforeTarget(pair<float, float> from, pair<float, float> target, float fromDistance,bool data) {
	int turn=0;
	if (data) {
		turn = 1;
	}
	float dist = distanceFromTarget(from, target);
	pair<float, float> coord = nextCoord;
	if (data && (turnToTarget == 1)) {
		turn = 0;
	}
	while (dist > fromDistance) {
		turn++;
		coord = evaluateNextCoord(coord, target);
		dist = distanceFromTarget(coord, target);
	}

	return turn;
}



class Player : public Entity {

public:
	// constructeurs
	Player();
	Player(float distperturn);

	//destructeur
	~Player();

	// attributs
	string action;
	int shotsFired;
	int kills;
	

	// méthodes
	float damageDeal(Enemy* enemy);
	int turnBeforeKill(Enemy* enemy);
	void think(map<int, Enemy*> enemies, map<int, struct data> datas, int totalEnemyLife, int dataCount);

};

Player::Player() { Entity(); }
Player::~Player(){}
Player::Player(float distperturn) :Entity(distperturn) { shotsFired = 0; kills = 0; }
float Player::damageDeal(Enemy* enemy) {
	float distFromEnemy = distance(currentCoord, enemy->nextCoord);
	float a = (125000.0f / pow(distFromEnemy, 1.2f));
	return round(a);
}
int Player::turnBeforeKill(Enemy* enemy) {
	int lifeTemp = enemy->life;
	int turn = 0;
	int dam = damageDeal(enemy);
	lifeTemp -= dam;
	while (lifeTemp > 0) {
		turn++;
		pair<int, int> nextP = enemy->evaluateNextCoord(enemy->nextCoord, enemy->destination);
		enemy->setNextCoord(nextP.first, nextP.second);
		dam = damageDeal(enemy);
		lifeTemp -= dam;
	}
	return turn;
}








bool isGameFinished(Player* player, map<int, Enemy*> enemies, int idEnemytarget,int& nbEnemy, int& dataCount, Enemy* dataNearestEnemy, string action) {

	bool finish = false;
	//cerr << to_string(dataNearestEnemy->turnToTarget) << endl;
	if ((action[0] == 'S') && (nbEnemy == 1) && (player->turnBeforeKill(enemies[idEnemytarget]) == 0)) {
		finish = true;
	}
	else if ((dataCount == 1) && (dataNearestEnemy->turnToTarget==0)) {
		finish = true;
		dataCount--;
	}
	return finish;
}

pair<float, float> getCoord(pair<float,float> playerCoord, Direction d, float distance) {

	pair<float, float> newCoord=playerCoord;
	if (d == Direction::UP) {
		newCoord.second -= distance;
	}
	if (d == Direction::DOWN) {
		newCoord.second += distance;
	}
	if (d == Direction::LEFT) {
		newCoord.first -= distance;
	}
	if (d == Direction::RIGHT) {
		newCoord.first += distance;
	}

	newCoord.first = newCoord.first > XMAX ? XMAX : newCoord.first;
	newCoord.first = newCoord.first < XMIN ? XMIN : newCoord.first;

	newCoord.second = newCoord.second > YMAX ? YMAX : newCoord.second;
	newCoord.second = newCoord.second < YMIN ? YMIN : newCoord.second;


	return newCoord;
}


pair<float, float> getCoordAngle(pair<float, float> playerCoord, float angle, float distance) {
	

	float angleCopy = (angle*PI / 180.0f);
	pair<float, float> newCoord = playerCoord;
	newCoord.first += distance* cos(angleCopy);
	newCoord.second += distance* sin(angleCopy);

	

	//cerr << "angle : " << angle << ", " << cos(angleCopy)<<" , "<<sin(angleCopy) << endl;
	//cerr << displayCoord(newCoord) << endl;
	newCoord.first = newCoord.first > XMAX ? XMAX : newCoord.first;
	newCoord.first = newCoord.first < XMIN ? XMIN : newCoord.first;

	newCoord.second = newCoord.second > YMAX ? YMAX : newCoord.second;
	newCoord.second = newCoord.second < YMIN ? YMIN : newCoord.second;

	return newCoord;

}


vector<Enemy*> nearestEnemiesFromPlayer(map<int, Enemy*> enemies, pair<float, float> coord) {
	vector<Enemy*> PlayerNearestEnemies;
	map<int, Enemy*>::iterator itEnemies;
	for (itEnemies = enemies.begin(); itEnemies != enemies.end(); ++itEnemies) {
		int dist = itEnemies->second->distanceFromTarget(coord, itEnemies->second->nextCoord);
		//cerr <<displayCoord(coord)<< " "<< itEnemies->second->id <<" "<<displayCoord(itEnemies->second->nextCoord) <<" "<<dist << endl;
		//cerr << displayCoord(coord) << " " << itEnemies->second->id << " " << dist << endl;
		if (dist <= 2000.0f) {
			PlayerNearestEnemies.push_back(itEnemies->second);
		}
	}
	return PlayerNearestEnemies;
}

//Enemy* nearestEnemyFromData(map<int, Enemy*> enemies) {
//	int turnsToTarget = 100;
//	Enemy* dataNearestEnemy;
//	map<int, Enemy*>::iterator itEnemies;
//	for (itEnemies = enemies.begin(); itEnemies != enemies.end(); ++itEnemies) {
//		int turn = itEnemies->second->turnToTarget;
//		if (turn < turnsToTarget) {
//			turnsToTarget = turn;
//			dataNearestEnemy = itEnemies->second;
//		}
//	}
//	return dataNearestEnemy;
//}

Enemy* nearestEnemyFromData(vector<Enemy*> enemies) {
	int turnsToTarget = 100;
	Enemy* dataNearestEnemy;
	for (int i = 0; i < enemies.size();i++) {
		int turn = enemies[i]->turnToTarget;
		if (turn < turnsToTarget) {
			turnsToTarget = turn;
			dataNearestEnemy = enemies[i];
		}
	}
	return dataNearestEnemy;
}


map<int, vector<Enemy*>> EnemiesPerData(map<int, Enemy*> enemies, map<int, struct data> datas) {
	
	map<int, vector<Enemy*>> ePerData;

	map<int, Enemy*>::iterator itEnemies;
	for (itEnemies = enemies.begin(); itEnemies != enemies.end(); ++itEnemies) {
		int idData = itEnemies->second->idTarget;
		ePerData[idData].push_back(itEnemies->second);
	}

	
	map<int, vector<Enemy*>>::iterator itePerData;
	for (itePerData = ePerData.begin(); itePerData != ePerData.end(); ++itePerData) {
		int idData = itePerData->first;
		vector<Enemy*> evec = itePerData->second;
		vector<Enemy*> EInOrder;
		for (int i = 0; i < evec.size(); i++) {
			Enemy* e = evec[i];
			//int turnTarget = e->turnToTarget;
			float distToTarget = distance(e->nextCoord, datas[idData].coord);
			int j = 0;
			int taille = EInOrder.size();
			while ((j < taille) && (distToTarget > distance(EInOrder[j]->nextCoord,datas[idData].coord ))) {
				j++;
			}
			if (j == taille) {
				EInOrder.push_back(e);
			}
			else {
				EInOrder.insert(EInOrder.begin() + j, e);
			}
		}
		ePerData[idData] = EInOrder;
	}

	//// TEST
	/*for (itePerData = ePerData.begin(); itePerData != ePerData.end(); ++itePerData) {
		int idData = itePerData->first;
		vector<Enemy*> evec = itePerData->second;
		cerr << " DATA " << idData << endl;
		for (int i = 0; i < evec.size(); i++) {
			Enemy* e = evec[i];
			cerr << e->turnToTarget << endl;
		}
		cerr << "***" << endl;
	}*/





	return ePerData;
}


bool isDataSafe(Player* p, struct data d, vector<Enemy*> enemies) {

	bool safe = false;
	int killsTurn = 0;
	int turnstotarget = 0;
	int i = 0;
	int taille = enemies.size();
	while ( (i<taille) && (killsTurn <= turnstotarget) ) {
		pair<float, float> nextCoordCopy = enemies[i]->nextCoord;
		int turnTargetCOpy = enemies[i]->turnToTarget;
		for (int j = 0; j < i; j++) {
			pair<int, int> nextP = enemies[i]->evaluateNextCoord(enemies[i]->nextCoord, enemies[i]->destination);
			enemies[i]->setNextCoord(nextP.first, nextP.second);
			turnTargetCOpy--;
		}
		//cerr<<"Ennemi "<<
		killsTurn += p->turnBeforeKill(enemies[i]);
		turnstotarget = turnTargetCOpy;
		enemies[i]->setNextCoord(nextCoordCopy.first, nextCoordCopy.second);
		i++;
	}

	if (killsTurn <= turnstotarget) {
		safe = true;
	}

	return safe;
}


struct data nearestDataFmPlayer(Player* p, map<int, struct data> datas) {

	struct data d;
	float distmin = 100000.0f;
	int idData = -1;
	map<int, struct data>::iterator itData;
	for (itData = datas.begin(); itData != datas.end(); ++itData) {
		float dist = distance(p->currentCoord, itData->second.coord);
		if (dist < distmin) {
			distmin = dist;
			idData = itData->first;
		}
	}

	return datas[idData];
}

pair<int, int> nextPLayerCoord(Player* p, map<int, Enemy*> enemies, map<int, struct data> datas,int dataCount) {

	vector<Enemy*> EnemiesNearPlayer = nearestEnemiesFromPlayer(enemies, p->currentCoord);
	// MOVE de façon à éviter ça
	float xAvg, yAvg;
	map<int, struct data>::iterator it;
	for (it = datas.begin(); it != datas.end(); ++it) {
		xAvg += it->second.coord.first;
		yAvg += it->second.coord.second;
	}
	xAvg /= dataCount;
	yAvg /= dataCount;

	int turn = 2;
	pair<float, float> destinationTemp;
	pair<int, int> nextC;
	pair<float, float> vecPlayerToEcoord;


	pair<float, float> ennemisCoord;
	float  eXAvg, eYAvg;
	eXAvg = eYAvg = 0.0f;
	int nbEnemies = 0;
	for (int i = 0; i < EnemiesNearPlayer.size(); i++) {
		Enemy* e = EnemiesNearPlayer[i];
		//cerr << displayCoord(e->nextCoord) << endl;
		eXAvg += e->nextCoord.first;
		eYAvg += e->nextCoord.second;
		nbEnemies++;
	}
	eXAvg /= nbEnemies;
	eYAvg /= nbEnemies;
	ennemisCoord.first = eXAvg;
	ennemisCoord.second = eYAvg;

	// Vecteur du player vers le point

	vecPlayerToEcoord = vecCoord(ennemisCoord, p->currentCoord);
	pair<float, float> vec = vecPlayerToEcoord;
	float length = vectorLength(vecPlayerToEcoord);
	pair<float, float> res;

	float dists[1] = { 1000.0f };
	int numEnum = 0;
	int numDistance = 0;
	float angleTurn = 0.0f;
	float baseAngle = 90.0f;
	int distTurn = 0;
	while (!EnemiesNearPlayer.empty()) {
		//cerr << "turn " << turn << endl;
		if (turn< 2) {
			struct data d = nearestDataFmPlayer(p, datas);
			pair<float, float> vecDataToPcoord = vecCoord(d.coord, p->currentCoord);
			float vecL= vectorLength(vecDataToPcoord);
			res = nextLocation(vecDataToPcoord, vecL, dists[distTurn]);
			nextC.first = (floor)(p->currentCoord.first + res.first);
			nextC.second = (floor)(p->currentCoord.second + res.second);
		}
		else if (turn < 3) { // MOYENNE COORD ENNEMIS DIRECTION OPPOSE AU POINT
			//cerr << "dist : " << distTurn << endl;
			res = nextLocation(vec, length, dists[distTurn]);
			nextC.first = (floor)(p->currentCoord.first + res.first);
			nextC.second = (floor)(p->currentCoord.second + res.second);
		}
		else if (turn == 3) {
			destinationTemp = make_pair(xAvg, yAvg);
			nextC = p->evaluateNextCoord(p->currentCoord, destinationTemp);
		}
		else {
			float angle = baseAngle * angleTurn;

			destinationTemp = getCoordAngle(p->currentCoord, angle, dists[numDistance]);
			angleTurn += 1.0f;
			if (angle >= 360.0f) {
				angleTurn = 0.0f;
				numDistance++;
				if (numDistance > 3) {
					baseAngle -= 5.0f;
					numDistance = 0;
				}
			}

			nextC = p->evaluateNextCoord(p->currentCoord, destinationTemp);
			//cerr << displayCoord(destinationTemp) << endl;
		}

		cerr << displayCoord(nextC) << endl;
		EnemiesNearPlayer = nearestEnemiesFromPlayer(enemies, nextC);
		turn++;
	}

	return nextC;
}


bool isDataSafeAnticipate(Player* p, struct data d, vector<Enemy*> enemies, int& shotsFired) {
	bool safe = false;
	int killsTurn = 0;
	int turnstotarget = 0;
	int i = 0;
	int taille = enemies.size();
	while ((i<taille) && (killsTurn <= turnstotarget)) {

		pair<float, float> nextCoordCopy = enemies[i]->nextCoord;
		int turnTargetCOpy = enemies[i]->turnToTarget;
		for (int j = 0; j < i; j++) {
			pair<int, int> nextP = enemies[i]->evaluateNextCoord(enemies[i]->nextCoord, enemies[i]->destination);
			enemies[i]->setNextCoord(nextP.first, nextP.second);
			turnTargetCOpy--;
		}
		//cerr<<"Ennemi "<<
		killsTurn += p->turnBeforeKill(enemies[i]);
		shotsFired += killsTurn + 1;
		turnstotarget = turnTargetCOpy;
		//cerr << "killsTurn : " << killsTurn << " ,  turntoTarget : " << turnstotarget << endl;
		enemies[i]->setNextCoord(nextCoordCopy.first, nextCoordCopy.second);
		i++;
	}

	if (killsTurn <= turnstotarget) {
		safe = true;
	}

	return safe;
}

void Player::think(map<int, Enemy*> enemies, map<int, struct data> datas, int totalEnemyLife, int dataCount) {

	vector<Enemy*> EnemiesNearPlayer = nearestEnemiesFromPlayer(enemies, currentCoord);
	idTarget = -1;
	action = "";

	// Enemy <= 2000.0F de distance de moi au prochain tour -> bouger
	if (!EnemiesNearPlayer.empty()) {
		//cerr << "1" << endl;
		pair<int, int> nextC = nextPLayerCoord(this, enemies, datas,dataCount);
		action = "MOVE " + to_string(nextC.first) + " " + to_string(nextC.second);
	}
	else {
		cerr << "SECOND" << endl;
		map<int, vector<Enemy*>> ePerData = EnemiesPerData(enemies, datas);

		struct data nearestDataFromPlayer;
		float distDataFromPlayer = 99999.0f;

		bool dataSafe = false;

		pair<float, float> destinationTemp;
		pair<int, int> nextC;

		map<int, vector<Enemy*>>::iterator itEPerData = ePerData.begin();
		int shotsMin = 100;

		while ( (itEPerData!=ePerData.end()) && (!dataSafe) ) {
		
			/*int idData = itEPerData->first;
			struct data d = datas[idData];
			float dist = distance(currentCoord, d.coord);
			if (dist < distDataFromPlayer) {
				destinationTemp = make_pair(d.coord.first, d.coord.second);
				nextC = evaluateNextCoord(currentCoord, destinationTemp);
				EnemiesNearPlayer = nearestEnemiesFromPlayer(enemies, nextC);
				if (EnemiesNearPlayer.empty()) {
					distDataFromPlayer = dist;
					nearestDataFromPlayer = d;
					action = "MOVE " + to_string((int)d.coord.first) + " " + to_string((int)d.coord.second);
				}			
			}*/
			int idData = itEPerData->first;
			struct data d = datas[idData];
			int shotsFired = 0;
			vector<Enemy*> dataEnemies = itEPerData->second;
			dataSafe=isDataSafeAnticipate(this, d, dataEnemies,shotsFired);
			//cerr << " I/ shotsF : " << shotsFired << " , shotsMin : " << shotsMin << endl;
			if ( (dataSafe) && (shotsFired <= shotsMin) ) {
				Enemy* eDataNearest = dataEnemies[0];
				shotsMin = shotsFired;
				idTarget = eDataNearest->id;
				action = "SHOOT " + to_string(idTarget);

				if (dataEnemies[0]->turnToTarget != 0) {

					// UPDATE PLAYER POS
					pair<float, float> pCurrentCoordCopy = this->currentCoord;
					this->currentCoord = evaluateNextCoord(currentCoord, eDataNearest->nextCoord);


					// GAMEOVER?
					vector<Enemy*> EnemiesNearPlayer = nearestEnemiesFromPlayer(enemies, currentCoord);

					// UPDATE ENEMIES POS
					for (int i = 0; i < dataEnemies.size(); i++) {
						dataEnemies[i]->setNextCoordTemp(dataEnemies[i]->nextCoord.first, dataEnemies[i]->nextCoord.second);
						pair<int, int> nextP = dataEnemies[i]->evaluateNextCoord(dataEnemies[i]->nextCoord, dataEnemies[i]->destination);
						dataEnemies[i]->setNextCoord(nextP.first, nextP.second);
						dataEnemies[i]->turnToTargetTemp = dataEnemies[i]->turnToTarget;
						dataEnemies[i]->turnToTarget = dataEnemies[i]->turnBeforeTarget(dataEnemies[i]->nextCoord, dataEnemies[i]->destination, dataEnemies[i]->distPerTurn, true);

					}

					if (EnemiesNearPlayer.empty()) {
						shotsFired = 0;
						dataSafe = isDataSafeAnticipate(this, d, dataEnemies, shotsFired);
						//cerr << " II/ shotsF : " << shotsFired << " , shotsMin : " << shotsMin << endl;
						//cerr << "E1TurnTarget : " << dataEnemies[0]->turnToTarget << endl;
						if ((dataSafe) && (shotsFired <= shotsMin)) {
							shotsMin = shotsFired;
							action = "MOVE " + to_string((int)this->currentCoord.first) + " " + to_string((int)this->currentCoord.second);
						}
					}

					//*** ON REMET LES BONNES VARIABLES
					// PLAYER
					currentCoord = pCurrentCoordCopy;
					// ENNEMIS
					for (int i = 0; i < dataEnemies.size(); i++) {
						dataEnemies[i]->setNextCoord(dataEnemies[i]->nextCoordTemp.first, dataEnemies[i]->nextCoordTemp.second);
						dataEnemies[i]->turnToTarget = dataEnemies[i]->turnToTargetTemp;
					}


				}

				
			}
			itEPerData++;
		}

		if (action == "") {
			cerr << "THIRD" << endl;
			int turntoTarMin = 100;
			int turntoKillMin = 100;
			int idKillMin = -1;
			map<int, Enemy*>::iterator itEnemies;
			for (itEnemies = enemies.begin(); itEnemies != enemies.end(); ++itEnemies) {
				int turntoTar = itEnemies->second->turnToTarget;
				pair<int, int> nextCo = itEnemies->second->nextCoord;
				int turnBefKill = turnBeforeKill(itEnemies->second);
				itEnemies->second->setNextCoord(nextCo.first, nextCo.second);
				if ((turnBefKill <= turntoTar) && (turntoTar < turntoTarMin)) {
					turntoTarMin = turntoTar;
					idTarget = itEnemies->second->id;
				}
				if (turnBefKill < turntoKillMin) {
					turntoKillMin = turnBefKill;
					idKillMin = itEnemies->second->id;
				}
			}
			// Si turnbeforekill <= turnbeforetarget avec turnbeforetarget min
			if (idTarget != -1) {
				action = "SHOOT " + to_string(idTarget);
			}
			// sinon turnbeforekill min
			else {
				action = "SHOOT " + to_string(idKillMin);
			}

		}

	}

	/*int nbEnemy = enemies.size();
	bool b = isGameFinished(this, enemies, idTarget,nbEnemy, dataCount, dataNearestEnemy, action);
	if (b) {
		int score = computeScore(dataCount, totalEnemyLife, shotsFired, kills);
		cerr << to_string(score) << endl;
	}*/
	


}




void displayEnemies(map<int, Enemy*> enemies) {
	map<int, Enemy*>::iterator it;
	for (it = enemies.begin(); it != enemies.end(); ++it) {
		cerr << it->second->id << " , " << displayCoord(it->second->currentCoord) << " -> "<<displayCoord(it->second->nextCoord) << " , " << it->second->life << " , "<<it->second->turnToTarget<< endl;
	}

}

void deleteDeathEnemies(map<int, bool>& IdEnemiesTest, map<int, Enemy*>& Enemies,vector<int>& idEnemies) {

	vector<int> idTrue;
	for (int i = 0; i < idEnemies.size(); i++) {
		int id = idEnemies[i];
		if (!IdEnemiesTest[id]) {
			//cerr << "ID TO DELETE :" << id << endl;
			delete Enemies[id];
			Enemies.erase(id);	
		}
		else {
			idTrue.push_back(id);
		}
	}
	idEnemies.clear();
	for (int i = 0; i < idTrue.size(); i++) {
		idEnemies.push_back(idTrue[i]);
		//cerr << idTrue[i] << endl;
	}
}




int main()
{
	vector<int> IdEnemies;
	map<int, bool> IdEnemiesTest;
	map<int, Enemy*> Enemies;
	map<int, struct data> datas;
	Player* player = new Player(1000.0f);

	bool begin = true;
	int totalEnemyLife = 0;


    // game loop
    while (1) {

		// PLAYER

        int x;
        int y;
        cin >> x >> y; cin.ignore();
		player->setCurrentCoord(x, y);


		// DATA
		datas.clear();
        int dataCount;
        cin >> dataCount; cin.ignore();
        for (int i = 0; i < dataCount; i++) {
            int dataId;
            int dataX;
            int dataY;
            cin >> dataId >> dataX >> dataY; cin.ignore();

			
			struct data d;
			d.id = dataId;
			d.exist = true;
			d.coord = make_pair(dataX, dataY);
			datas[dataId] = d;
			
        }


		// ENEMY
		IdEnemiesTest.clear();

        int enemyCount;
        cin >> enemyCount; cin.ignore();

        for (int i = 0; i < enemyCount; i++) {
            int enemyId;
            int enemyX;
            int enemyY;
            int enemyLife;
            cin >> enemyId >> enemyX >> enemyY >> enemyLife; cin.ignore();
			//cerr << enemyId << " " << enemyLife << endl;

			if (begin) {
				totalEnemyLife += enemyLife;
			}
			else {
				IdEnemiesTest[enemyId] = true;
			}
			

			if (!IdEnemiesTest[enemyId]) {
				IdEnemiesTest[enemyId] = true;
				if (Enemies[enemyId] == nullptr) {
					IdEnemies.push_back(enemyId);
				}
				Enemy* e = new Enemy(500.0f, enemyX, enemyY, enemyId, enemyLife);
				Enemies[enemyId] = e;
				
			}
			else {
				Enemies[enemyId]->setCurrentCoord(enemyX, enemyY);
				Enemies[enemyId]->life = enemyLife;	
				Enemies[enemyId]->setDestination(-1, -1);
				Enemies[enemyId]->setNextCoord(-1, -1);
			}

			// Pour chaque ennemi, déterminer prochain emplacement
			Enemies[enemyId]->findDestination(datas);
			if (Enemies[enemyId]->idTarget != -1) {
				pair<int, int> nextP = Enemies[enemyId]->evaluateNextCoord(Enemies[enemyId]->currentCoord, Enemies[enemyId]->destination);
				Enemies[enemyId]->setNextCoord(nextP.first, nextP.second);
				Enemies[enemyId]->turnToTarget = Enemies[enemyId]->turnBeforeTarget(Enemies[enemyId]->nextCoord, Enemies[enemyId]->destination,Enemies[enemyId]->distPerTurn,true);
			}
			else {
				Enemies[enemyId]->turnToTarget = -1;
			}
        }
		begin = false;

		// Enlever chaque ennemi mort 
		deleteDeathEnemies(IdEnemiesTest,Enemies,IdEnemies);
		

		//
		/*int s = 0;
		vector<Enemy*> eTEst;
		bool das = isDataSafeAnticipate(player, datas[0], eTEst, s, 1);
		cerr << s << endl;*/


		//

		//displayEnemies(Enemies);
		clock_t start;
		start = clock();
		player->think(Enemies, datas,totalEnemyLife,dataCount);
		cerr << "Time : " << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << endl;
		

		cout << player->action << endl;

		
        //cout << "MOVE 8000 4500" << endl; // MOVE x y or SHOOT id
    }
}