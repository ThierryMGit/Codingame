#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int N;
    cin >> N; cin.ignore();
    int C;
    cin >> C; cin.ignore();

	int totalBudget = 0;
	int prixRestant = C;
	vector < pair<int, int>> budgetRestantDu;
	list<int> budgetDonne;
    for (int i = 0; i < N; i++) {
        int B;
        cin >> B; cin.ignore();
		totalBudget += B;
		pair<int, int> p;
		p.first = B;
		p.second = 0;
		budgetRestantDu.push_back(p);
    }

	if (totalBudget < C) {
		cout << "IMPOSSIBLE" << endl;
	}
	else {

		int moyenneDon;
		while (prixRestant > 0) {

			moyenneDon = prixRestant / budgetRestantDu.size();
			vector<int> idToDelete;
			//cerr << moyenneDon << endl;
			if (moyenneDon == 0) {
				for (int i = 0; i < prixRestant; i++) {
					pair<int, int> p = budgetRestantDu[i];
					budgetDonne.push_back(p.second + 1);
					idToDelete.push_back(i);
				}
				prixRestant = 0;
			}
			else
			{
				
				for (int i = 0; i < budgetRestantDu.size(); i++) {

					pair<int, int>p = budgetRestantDu[i];
					int budgetRestant = p.first;
					int budgetDu = p.second;
					if (budgetRestant <= moyenneDon) {
						budgetDonne.push_back(budgetRestant + budgetDu);
						prixRestant -= budgetRestant;
						idToDelete.push_back(i);
					}
					else {
						budgetRestantDu[i].first -= moyenneDon;
						budgetRestantDu[i].second += moyenneDon;
						prixRestant -= moyenneDon;
					}

				}
				
			}
			int x = 0;
			for (int i = 0; i < idToDelete.size(); i++) {

				budgetRestantDu.erase(budgetRestantDu.begin() + (idToDelete[i] - x));
				x++;
			}
		}
		for (int i = 0; i < budgetRestantDu.size(); i++) {
			pair<int, int>p = budgetRestantDu[i];
			int budgetDu = p.second;
			budgetDonne.push_back(budgetDu);
		}
		budgetDonne.sort();
		for (list<int>::iterator it = budgetDonne.begin(); it != budgetDonne.end(); it++) {
			cout << *it << endl;
		}
	}

	
	


    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

   // cout << "IMPOSSIBLE" << endl;
}