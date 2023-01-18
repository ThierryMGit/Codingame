#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

string nextNb(string line, int& index) {

	string nb = "";
	if (line[index] == ' ') {

		nb=" ";
	}
	else {
		
		while ((index < line.length()) && (line[index] != ' ')) {
			nb += string(1, line[index]);
			index++;
		}

	}
	return nb;
}

int main()
{
	int R;
	cin >> R; cin.ignore();
	int L;
	cin >> L; cin.ignore();

	string t = "";
	string result = "";

	result += to_string(R);
	for (int i = 0; i < L - 1; i++) {
		t = result;
		result = "";
		int j = 0;
		//cerr << "t : "<< t << endl;
		while (j < t.length()) {
			string s = nextNb(t,j);
			//cerr << "/ nb : " << s << endl;
			if (s != " ") {
				
				int x = j;
				//cerr << " j : " << j << ", x : " << x << endl;
				bool ok = true;
				int count = 1;
				string n = "";
				while ((x < t.length()) && (ok) ) {
					//cerr << " xavant : " << x << endl;
					n = nextNb(t, x);
					//cerr << "n : " << n << endl;
					//cerr << " xapres : " << x << endl;
					if (n == " ") {
						cerr << "blank" << endl;
						x++;
					}
					else if (n == s) {
						//cerr << "==" << endl;
						count++;
					}
					else {
						//cerr << "else" << endl;
						ok = false;
					}
					//x++;
				}
				//cerr << "count : "<<count << endl;
				//count = count - blank;
				if (result == "") {

					result += to_string(count) + " " + s;
				}
				else {
					result += " "+to_string(count) + " " + s;
				}
				if  (!ok){
					//cerr << " x: " << x << " / " << "n.length  : " << n.length() << endl;
					j = x - (n.length());
				}
				else {
					j = x;
				}
				
			}
			else {
				j++;
			}
			
		}
		//cerr << i << ": " << result << endl;
	}
	//cerr << result << endl;
	string final="";
	int x = 0;
	string n;
	while ((x < result.length())) {
		//cerr << " xavant : " << x << endl;
		n = nextNb(result, x);
		//cerr << "n : " << n << endl;
		//cerr << " xapres : " << x << endl;
		if (n == " ") {
			x++;
		}
		else  {
			if (x < result.length() - 1) {
				final += n + " ";
			}
			else {
				final += n;
			}
		}

	}

    cout << final << endl;
}