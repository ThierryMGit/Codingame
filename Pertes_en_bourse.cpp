#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int n;
    cin >> n; cin.ignore();

	vector<int> vec;
    for (int i = 0; i < n; i++) {
        int v;
        cin >> v; cin.ignore();
		vec.push_back(v);
		
    }
	int diff = numeric_limits<int>::min();
	int max = numeric_limits<int>::min();
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i] > max) {
			max = vec[i];
		}
		else {
			int calcul = max - vec[i];
			if (calcul > diff) {
				diff = calcul;
			}
		}
		
	}
	if (diff < 0) {
		diff = 0;
	}
	else {
		diff *= -1;
	}
	
    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;
    cout << diff << endl;
}