#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include<queue>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/


bool afterS2 = false;

struct Card {

	int value;
	int idJ;
};


class Player {

public:
	queue<Card> cardsToPlay;
	vector<Card> cardsCache;

	Player();
	int Stage1(Player& P, bool callFromS2);
	int Stage2(Player& P);
	void Afficher();
};

Player::Player() {}

int Player::Stage1(Player& P,bool callFromS2) { // ETAPE 1 : LE COMBAT
	afterS2 = callFromS2;

	if (!cardsToPlay.empty() && !P.cardsToPlay.empty()) {
		afterS2 = false;
		Card cardP1 = cardsToPlay.front();
		cardsToPlay.pop();
		cardsCache.push_back(cardP1);

		Card cardP2 = P.cardsToPlay.front();
		P.cardsToPlay.pop();
		P.cardsCache.push_back(cardP2);
		
		cerr << cardP1.value << " / " << cardP2.value << endl;
		if (cardP1.value > cardP2.value) {
			//cerr << "1 > 2" << endl;
			return 1;
			
		}
		if (cardP2.value > cardP1.value) {
			//cerr << "2 > 1" << endl;
			return 2;
		}
		if (cardP2.value == cardP1.value) {
			//cerr << "1 = 2" << endl;
			return Stage2(P);
		}
	}
	else {
		return 0;
	}
	return -1;
}

int Player::Stage2(Player& P) {
	cerr << " STAGE 2" << endl;
	if (cardsToPlay.size() >= 3) {
		for (int i = 0; i < 3; i++) {
			Card cardP1 = cardsToPlay.front();
			cardsToPlay.pop();
			cardsCache.push_back(cardP1);
		}
	}
	else {
		int taille = cardsToPlay.size();
		for (int i = 0; i < taille; i++) {
			Card cardP1 = cardsToPlay.front();
			cardsToPlay.pop();
			cardsCache.push_back(cardP1);
		}
	}

	if (P.cardsToPlay.size() >= 3) {
		for (int i = 0; i < 3; i++) {
			Card cardP2 = P.cardsToPlay.front();
			P.cardsToPlay.pop();
			P.cardsCache.push_back(cardP2);
		}
	}
	else {
		int taille = P.cardsToPlay.size();
		for (int i = 0; i < taille; i++) {
			Card cardP2 = P.cardsToPlay.front();
			P.cardsToPlay.pop();
			P.cardsCache.push_back(cardP2);
		}
	}
	return Stage1(P,true);
}

void Player::Afficher() {
	int taille = cardsToPlay.size();
	for (int i = 0; i < taille; i++) {
		Card cardP1 = cardsToPlay.front();
		cardsToPlay.pop();
		cerr << "card " << i << " : " << cardP1.value << endl;

	}
}


int val(char c) {

	int value = (int)(c - '0');
	if (value > 9) {
		if (c == 'A') {
			value = 14;
		}
		if (c == 'K') {
			value = 13;
		}
		if (c == 'Q') {
			value = 12;
		}
		if (c == 'J') {
			value = 11;
		}
	}
	return value;
}

 
int main()
{
    int n; // the number of cards for player 1
    cin >> n; cin.ignore();
	int nbManches = 0;
	Player J1;
    for (int i = 0; i < n; i++) {
        string cardp1; // the n cards of player 1
        cin >> cardp1; cin.ignore();
		for (int j = 0; j < cardp1.size(); j++) {
			struct Card c;
			if (cardp1.size() == 3) {
				c.value = 10;
				c.idJ = 1;
				J1.cardsToPlay.push(c);
				j = 3;
			}
			else {
				if (j % 2 == 0) {
					c.value = val(cardp1[j]);
					c.idJ = 1;
					J1.cardsToPlay.push(c);
					
				}
			}
		}
		//cerr << J1.cardsToPlay.back().value << endl;
    }
    int m; // the number of cards for player 2
    cin >> m; cin.ignore();
	Player J2;
    for (int i = 0; i < m; i++) {
        string cardp2; // the m cards of player 2
        cin >> cardp2; cin.ignore();
		for (int j = 0; j < cardp2.size(); j++) {
			struct Card c;
			if (cardp2.size() == 3) {
				c.value = 10;
				c.idJ = 1;
				J2.cardsToPlay.push(c);
				j = 3;
			}
			else {

				if (j % 2 == 0) {
					c.value = val(cardp2[j]);
					c.idJ = 2;
					J2.cardsToPlay.push(c);
				}
			}
			
		}
		//cerr << J2.cardsToPlay.back().value << endl;
    }
	
	int winner = 0;
	while (!J1.cardsToPlay.empty() && !J2.cardsToPlay.empty()) {
		
		nbManches++;
		cerr << " MANCHE " << nbManches << endl;
		cerr << endl;
		winner = J1.Stage1(J2,false);
		if (winner == 1) {
			for (int i = 0; i < J1.cardsCache.size(); i++) {
				J1.cardsToPlay.push(J1.cardsCache[i]);
			}
			for (int i = 0; i < J2.cardsCache.size(); i++) {
				J1.cardsToPlay.push(J2.cardsCache[i]);
			}
			J1.cardsCache.clear();
			J2.cardsCache.clear();
		}
		if (winner == 2) {
			for (int i = 0; i < J1.cardsCache.size(); i++) {
				J2.cardsToPlay.push(J1.cardsCache[i]);
			}
			for (int i = 0; i < J2.cardsCache.size(); i++) {
				J2.cardsToPlay.push(J2.cardsCache[i]);
			}
			J1.cardsCache.clear();
			J2.cardsCache.clear();
		}
	}

	if (afterS2) {
		cout << "PAT" << endl;
	}
	else {
		if (J1.cardsToPlay.empty()) {
			cout << 2 << " " << nbManches << endl;
		}
		else if (J2.cardsToPlay.empty()) {
			cout << 1 << " " << nbManches << endl;
		}
	}
	

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    
}