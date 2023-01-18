#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <math.h> 

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/


long long int getResult(long long int nb1, long long int nb2, string op) {

	long long int result;

	if (op == "+") {
		result = nb1 + nb2;
	}
	if (op == "*") {
		result = nb1 * nb2;
	}
	if (op == "/") {
		result = nb1 / nb2;
	}
	if (op == "-") {
		result = nb1 - nb2;
	}
		
	return result;
}



void resultAscii(map<int, int>& PuiNb, long long int result) {

	long long int res = result;
	int puissance = 10;
	long long int N = pow(20, puissance);
	//cerr << N << endl;
	while (res != 0) {

		if (N <= res) {
			res -= N;
			PuiNb[puissance]++;
		}
		else {
			puissance--;
			N= pow(20, puissance);
		}
		//cerr << res << endl;
	}

}

int main()
{
    int L;
    int H;
    cin >> L >> H; cin.ignore();
	map<int, string> NbToascii;
	map<string, int> asciiToNb;
    for (int i = 0; i < H; i++) {
        string numeral;
        cin >> numeral; cin.ignore();
		for (int j = 0; j < numeral.length(); j++) {

			char c = numeral[j];
			int nb = j / L;
			//cerr << nb << endl;
			if (i > 0) {
				if ((j == 0) || (j%L) == 0) {

					NbToascii[nb] += "\n" + string(1, c);
				}
				else {
					NbToascii[nb] += string(1, c);
				}
			}
			else {
				NbToascii[nb] += string(1, c);
			}
		}

    }

	for (int j = 0; j < 20; j++) {

		asciiToNb[NbToascii[j]] = j;
		//cerr << NbToascii[j];// << " " << asciiToNb[NbToascii[j]] << endl;
		//cerr << endl;
		
	}
	


    int S1;
    cin >> S1; cin.ignore();
	long long int nb1=0;
	int nbpuissance = (S1 / H)-1;
	//cerr << nbpuissance << endl;
	string s = "";
    for (int i = 0; i < S1; i++) {
        string num1Line;
        cin >> num1Line; cin.ignore();
		//cerr << s << endl;
		if ( (i!=0) && ((i%H) == 0) ) {
			//cerr << i << " " << H << endl;
			//cerr << s << endl;
			nb1 += (asciiToNb[s] * pow(20, nbpuissance));
			nbpuissance -= 1;
			s = "";
		}
		for (int j = 0; j < num1Line.length(); j++) {
			char c = num1Line[j];
			if (i > 0) {
				if ( (j == 0) && ((i%H)!=0) )  {

					s += "\n" + string(1, c);
				}
				else {
					s += string(1, c);
				}
			}
			else {
				s += string(1, c);
			}
			//cerr << s << endl;
			//cerr << endl;
		}

    }
	//cerr << "1";
	//cerr << s << endl;
	//cerr << asciiToNb[s] << " " <<nbpuissance<<" " <<pow(20, nbpuissance) << endl;
	nb1 += (asciiToNb[s] * pow(20, nbpuissance));
	//cerr << nb1 << endl;

    int S2;
    cin >> S2; cin.ignore();
	long long int nb2=0;
	nbpuissance = (S2 / H) - 1;
	s = "";
    for (int i = 0; i < S2; i++) {
        string num2Line;
        cin >> num2Line; cin.ignore();
		if ((i != 0) && ((i%H) == 0)) {
			//cerr << i << " " << H << endl;
			//cerr << s << endl;
			nb2 += (asciiToNb[s] * pow(20, nbpuissance));
			nbpuissance -= 1;
			s = "";
		}
		for (int j = 0; j < num2Line.length(); j++) {
			char c = num2Line[j];
			if (i > 0) {
				if ((j == 0) && ((i%H) != 0)) {

					s += "\n" + string(1, c);
				}
				else {
					s += string(1, c);
				}
			}
			else {
				s += string(1, c);
			}
			//cerr << s << endl;
			//cerr << endl;
		}
    }
	nb2 += (asciiToNb[s] * pow(20, nbpuissance));
	//cerr << nb2 << endl;
    string operation;
    cin >> operation; cin.ignore();
	//cerr << operation << endl;


	long long int result = getResult(nb1, nb2, operation);
	//cerr << result << endl;

	map<int, int> PuiNb;
	string s2 = "";
	if (result == 0) {
		s2 = NbToascii[0];
	}
	else {
		resultAscii(PuiNb, result);
		bool begin = false;
		for (int i = 10; i >= 0; i--) {
			int n = PuiNb[i];
			//cerr << i << " " << n << endl;
			if (begin) {
				if (i >= 0) {
					s2 += "\n" + NbToascii[n];
				}
				/*else {

				}*/
			}
			if ((n > 0) && (!begin)) {
				begin = true;
				s2 += NbToascii[n];
			}
			//cerr << s2 << endl;
			//cerr << endl;

		}
		//cerr << s << endl;
	}
	

	
	

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << s2 << endl;
}