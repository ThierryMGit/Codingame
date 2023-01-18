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



void changeDepth(map<int, int>& nodeDepth, vector<int> nodeId, int sourceDepth, map<int,vector<int>> influences) {

	for (int i = 0; i < nodeId.size(); i++) {
		nodeDepth[nodeId[i]] = sourceDepth >= nodeDepth[nodeId[i]] ? sourceDepth + 1 : nodeDepth[nodeId[i]];
		changeDepth(nodeDepth, influences[nodeId[i]], nodeDepth[nodeId[i]], influences);
	}
}


int main()
{
    int n; // the number of relationships of influence
    cin >> n; cin.ignore();

	map<int, vector<int>> influences;
	map<int, int> nodeDepth;
    for (int i = 0; i < n; i++) {
        int x; // a relationship of influence between two people (x influences y)
        int y;
        cin >> x >> y; cin.ignore();
		influences[x].push_back(y);
		int oldDepth = nodeDepth[y];
		nodeDepth[y]=nodeDepth[x]>=nodeDepth[y]? nodeDepth[x] + 1 : nodeDepth[y];
		if (oldDepth != nodeDepth[y]) {
			changeDepth(nodeDepth, influences[y], nodeDepth[y],influences);
		}	
    }
	map<int, int>::iterator p;
	int lmax = 0;
	for (p = nodeDepth.begin(); p != nodeDepth.end(); p++)
	{
		if (p->second > lmax) {
			lmax = p->second;
		}
	}

    cout << to_string(lmax+1) << endl;
}