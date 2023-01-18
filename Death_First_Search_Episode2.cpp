#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <utility>

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
	int depth;
	bool seen;
	int nbBlank;

	Node(int i);
	void addLink(Node* n);
	void eraseLink(Node* n);
	void resetNode();
	void setDepth(int d);
	void setSeen(bool b);
	void setBlank(int n);
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

void Node::resetNode() {
	depth = 0;
	seen = false;
	nbBlank = 0;
}

void Node::setDepth(int d) {
	depth = d;
}

void Node::setSeen(bool b) {
	seen = b;
}

void Node::setBlank(int n) {
	nbBlank = n;
}

void resetNodes(vector<Node*>& nodesList) {

	for (int i = 0; i < nodesList.size(); i++) {
		nodesList[i]->resetNode();
	}

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
		nodesList[SI]->setSeen(true);
		resetNodes(nodesList);
		int depth = 0;
		

		map<int, bool> nbGatewayOK;
		map<int, pair<int, int>>linkToDestroy;
		nbGatewayOK[1] = false;
		nbGatewayOK[2] = false;

		while ( (!found) && (!file.empty()) ) {
			//cerr << "1" << endl;
			Node* node = file.front();
			node->setSeen(true);
			file.pop();
			depth = node->depth;
			map<int, Node*> nodeLinks = node->links;
			map<int, Node*>::iterator it = nodeLinks.begin();
			int idGateway;
			//cerr << "Node : " << node->id << endl;
			int nbGateway = 0;
			//cerr << "id Node : " << node->id << endl;
			//cerr << "2" << endl;

			


			
			//cerr << "VOISINS" << endl;
			while (it != nodeLinks.end())  {
				
				
				if (it->second->gateway) {
					nbGateway++;
					idGateway = it->second->id;
				}
				else {
					if (!it->second->seen) {
						it->second->setSeen(true);
						it->second->setDepth(node->depth + 1);
						file.push(it->second);
					}
					
				}
				it->second->setSeen(true);
				it++;
			}
			//cerr << "3" << endl;

			

			
			it = nodeLinks.begin();
			while (it != nodeLinks.end()) {
			
				if (node->depth < it->second->depth) {
					if (nbGateway == 0) {
						it->second->setBlank(node->nbBlank + 1);
					}
					else {
						it->second->setBlank(node->nbBlank);
					}
					
				}
				//cerr << "id : " << it->second->id << ", blank " << it->second->nbBlank << endl;
				it++;
			}
			

			//cerr << "Gateways : " << nbGateway << ", blank " << node->nbBlank << endl;

			if ((nbGateway > 0) && (depth==0) ) {
				idN1 = idGateway;
				found = true;

			}
			else {
				if (nbGateway == 1) {
					//cerr << "nbGateway == 1" << endl;
					nbGatewayOK[1] = true;
					pair<int,int> p= make_pair(idGateway, node->id);
					linkToDestroy[1].swap(p);
					//cerr << linkToDestroy[1].first << " " << linkToDestroy[1].second << endl;
					//linkToDestroy[1] = make_pair(idGateway, node->id);
				}

				if (nbGateway > 1) {
					//cerr << "nbGateway > 1" << endl;
					if (node->nbBlank <= 1) {
						//cerr << "1" << endl;
						idN1 = idGateway;
						found = true;
					}
					else {
						//cerr << "2" << endl;
						nbGatewayOK[2] = true;
						pair<int, int> p = make_pair(idGateway, node->id);
						linkToDestroy[2].swap(p);
						//cerr << linkToDestroy[2].first << " " << linkToDestroy[2].second << endl;
						//linkToDestroy[2] = make_pair(idGateway, node->id);
					}
				}

			}
		

			if (found) {
				idN2 = node->id;
				nodesList[idN1]->eraseLink(nodesList[idN2]);
				nodesList[idN2]->eraseLink(nodesList[idN1]);
			}
			//cerr << "4" << endl;
			
		}

		cerr << found << endl;
		if (!found) {
			pair<int, int> firstLinkToDestroy;
			if (nbGatewayOK[1]) {
				firstLinkToDestroy = linkToDestroy[1];
				//cerr << linkToDestroy[1].first << " " << linkToDestroy[1].second << endl;
			}
			if (nbGatewayOK[2]) {
				firstLinkToDestroy = linkToDestroy[2];
				//cerr << linkToDestroy[2].first << " " << linkToDestroy[2].second << endl;
			}
			idN1 = firstLinkToDestroy.first;
			idN2 = firstLinkToDestroy.second;
			//cerr << idN1 << " " << idN2 << endl;
			nodesList[idN1]->eraseLink(nodesList[idN2]);
			nodesList[idN2]->eraseLink(nodesList[idN1]);
		}

		// Write an action using cout. DON'T FORGET THE "<< endl"
		// To debug: cerr << "Debug messages..." << endl;

		cout << idN1 << " " << idN2 << endl; // Example: 0 1 are the indices of the nodes you wish to sever the link between
	}
}