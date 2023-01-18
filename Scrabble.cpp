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

void initletterPoint(map<char, int>& lP)
{
	lP['e'] = lP['a'] = lP['i'] = lP['o'] = lP['n'] = lP['r'] = lP['t'] = lP['l'] = lP['s'] = lP['u'] = 1;
	lP['d'] = lP['g'] = 2;
	lP['b'] = lP['c'] = lP['m'] = lP['p'] = 3;
	lP['f'] = lP['h'] = lP['v'] = lP['w'] = lP['y'] = 4;
	lP['k'] = 5;
	lP['j'] = lP['x'] = 6;
	lP['q'] = lP['z'] = 7;
}

bool contain(vector<char> lByP, char c) {

	int j = 0;
	bool found = false;
	while ((j<lByP.size()) && (!found)) {
		if (lByP[j] == c) {
			found = true;
		}
		j++;
	}

	return found;
}


//void getWords(vector )


int main()
{
    int N;
    cin >> N; cin.ignore();
	map<char, int> letterPoint;
	initletterPoint(letterPoint);

	map<string, int> wordPoint;
	map<string, int> wordRank;
	map<int, map<char, bool>> letterPlace;
	map<int, vector<char>> PlettersByPlace;
	map<int, map<string, bool>> existCombi;
	int largestWord = 0;
    for (int i = 0; i < N; i++) {
        string W;
        getline(cin, W);
		wordRank[W] = i;
		int score = 0;
		int size = W.length();
		for (int j = 0; j < size; j++) {
			letterPlace[j][W[j]] = true;
			score += letterPoint[W[j]];
			string t = W.substr(0, j + 1);
			/*if (W == "satire") {
				cerr << t << " "<<j+1<< endl;
			}*/
			
			existCombi[j + 1][t] = true;
		}
		wordPoint[W] = score;
		if (size > largestWord) {
			largestWord = size;
		}
    }
    string LETTERS;
    getline(cin, LETTERS);
	map<char, int> nbPLetters;
	for (int i = 0; i < LETTERS.length(); i++) {
		char c=LETTERS[i];
		nbPLetters[c]++;
		for (int j = 0; j < min(largestWord,7) ; j++) {
			if (letterPlace[j][c]) {
				if (!contain(PlettersByPlace[j], c)) {
					PlettersByPlace[j].push_back(c);
				}
				
			}
		}
	}

	//cerr <<"a " <<nbPLetters['a'] << endl;

	/*for (int i = 0; i < min(largestWord,7); i++) {
		vector<char> vec = PlettersByPlace[i];
		cerr << " Emplacement "<<i << endl;
		for (int j = 0; j < vec.size(); j++) {
			cerr << vec[j] << " / ";
		}
		cerr << endl;
	}*/

	vector<string> PossibleWords;
	vector<string> testWords;
	map<string, map<char, int>> PLettersInWord;
	//vector<string> tested
	int maxscore = 0;
	int minRank = N;

	for (int i = 0; i < min(largestWord,7); i++) {
		//cerr << i << endl;
		vector<char> charVec = PlettersByPlace[i];
		vector<string> testWordsTemp;

		for (int j = 0; j < charVec.size(); j++) {
			char c = charVec[j];
			//cerr << " " << j << endl;
			for (int k = 0; k < testWords.size(); k++) {
				//cerr << "  " << k << endl;
				//cerr << testWords[k] << " / " << c << " : " << PLettersInWord[testWords[k]][c] << endl;
				if (PLettersInWord[testWords[k]][c] < nbPLetters[c]) {
					
					string s = testWords[k] + string(1, c);
		
					if (existCombi[s.length()][s]) {
						PLettersInWord[s] = PLettersInWord[testWords[k]];
						PLettersInWord[s][c]++;
						//cerr << PLettersInWord[s][c] << endl;
						testWordsTemp.push_back(s);
						int points = wordPoint[s];
						if (points > 0) {
							if ( (points > maxscore)  || ( (points == maxscore) && ( wordRank[s] < minRank) ) ){
								PossibleWords.erase(PossibleWords.begin(), PossibleWords.end());
								PossibleWords.push_back(s);
								maxscore = points;
								minRank = wordRank[s];
							}
							/*else if (points == maxscore) {
								PossibleWords.push_back(s);
							}*/
						}
					}
				}
			
			}
			if (i == 0) {
				PLettersInWord[string(1, c)][c]=1;
				testWordsTemp.push_back(string(1, c));
			}
		}
		testWords = testWordsTemp;
	}


	/*for (int i = 0; i < PossibleWords.size(); i++) {
		cerr << PossibleWords[i] << endl;
	}*/

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << PossibleWords[0] << endl;
}