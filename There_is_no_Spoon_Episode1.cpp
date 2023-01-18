#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Don't let the machines win. You are humanity's last hope...
 **/


class Cell {

public:
	string coord;
	bool empty = true;
	string rightN="-1 -1";
	string bottomN= "-1 -1";

	Cell();
};

Cell::Cell(){}



int main()
{
    int width; // the number of cells on the X axis
    cin >> width; cin.ignore();
    int height; // the number of cells on the Y axis
    cin >> height; cin.ignore();
	vector<Cell> v;
	vector<string> Lines;
	for (int j = 0; j < height; j++) {
		string line; // width characters, each either 0 or .
		getline(cin, line);
		cerr << line << endl;
		for (int i = 0; i < line.size(); i++) {
			Cell c;
			v.push_back(c);
			if (line[i] == '0') {
				v[i+width*j].coord = to_string(i) + " " + to_string(j);
				//cerr << v[i + width*j].coord << endl;
				v[i + width*j].empty = false;
				if (i != 0) {
					int x = i-1;
					while ( (x >= 0) && (line[x] != '0') ) {
						x--;
					}
					if (x >= 0) {
						v[(x + width*j)].rightN = to_string(i) + " " + to_string(j);
					}
				}
				//cerr << j << endl;
				if (j > 0) {
					int x = j-1 ;
					while ((x >= 0) && (Lines[x][i] != '0')) {
						x--;
					}
					if (x >= 0) {
						v[(i + width*x)].bottomN = to_string(i) + " " + to_string(j);
					}
				}
			}
		}
		Lines.push_back(line);
	}

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;
	for (int i = 0; i < v.size(); i++) {
		if (!v[i].empty) {
			cout << v[i].coord+" "+v[i].rightN +" "+v[i].bottomN<< endl;
		}
	}
   // cout << "0 0 1 0 0 1" << endl; // Three coordinates: a node, its right neighbor, its bottom neighbor
}