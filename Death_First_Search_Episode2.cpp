#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <queue> 

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/



 class Node {

 public:
	 map<int, Node*> links;
	 bool gateway;
	 int id;

	 Node(int i);
	 void addLink(Node* n);
	 void eraseLink(Node* n);
};

 Node::Node(int i) {
	 gateway = false;
	 id = i;
 }

 void Node::addLink(Node* n) {
	 links[n->id] = n;
 }

 void Node::eraseLink(Node* n) {
	 map<int, Node*>::iterator it;
	 it = links.find(n->id);
	 links.erase(it);
 }


int main()
{
    int N; // the total number of nodes in the level, including the gateways
	
    int L; // the number of links
    int E; // the number of exit gateways
    cin >> N >> L >> E; cin.ignore();
	vector<Node*> nodesList;
	for (int i = 0; i < N; i++) {
		Node* n = new Node(i);
		nodesList.push_back(n);
	}
    for (int i = 0; i < L; i++) {
        int N1; // N1 and N2 defines a link between these nodes
        int N2;
        cin >> N1 >> N2; cin.ignore();
		nodesList[N1]->addLink(nodesList[N2]);
		nodesList[N2]->addLink(nodesList[N1]);
    }

    for (int i = 0; i < E; i++) {
        int EI; // the index of a gateway node
        cin >> EI; cin.ignore();
		nodesList[EI]->gateway = true;
    }

    // game loop
    while (1) {
        int SI; // The index of the node on which the Skynet agent is positioned this turn
        cin >> SI; cin.ignore();
		bool found = false;
		int idN1, idN2;
		queue<Node*> file;
		file.push(nodesList[SI]);
		while (!found) {
			Node* node = file.front();
			file.pop();
			map<int, Node*> nodeLinks = node->links;
			map<int, Node*>::iterator it = nodeLinks.begin();
			while( (it != nodeLinks.end()) && (!it->second->gateway) ){
				file.push(it->second);
				it++;
			}
			if (it != nodeLinks.end()) {
				idN1 = it->first;
				found = true;
			}
			else if ((it == nodeLinks.end()) && (it--->second->gateway)) {
				idN1 = it--->first;
				found = true;
			}
			if (found) {
				idN2 = node->id;
				nodesList[idN1]->eraseLink(nodesList[idN2]);
				nodesList[idN2]->eraseLink(nodesList[idN1]);
			}
		}

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        cout <<idN1 << " " << idN2<< endl; // Example: 0 1 are the indices of the nodes you wish to sever the link between
    }
}