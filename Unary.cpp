#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdio>

using namespace std;

/**
* Auto-generated code below aims at helping you parse
* the standard input according to the problem statement.
**/



string letterToBinary(char letter)
{
	int number = int(letter);
	string binaryNumber = "";
	do {
		binaryNumber.insert(0, to_string(number % 2));
		number /= 2;
	} while (binaryNumber.size() != 7);
	return binaryNumber;
}


string chuckNorris(string binaryLetter) {
	string norrisLetter = "";
	int i = 0;
	while (i < binaryLetter.size()) {
		if (binaryLetter[i] == '1') {
			norrisLetter += "0 ";
		}
		else {
			norrisLetter += "00 ";
		}
		char letter = binaryLetter[i];
		while ((i < binaryLetter.size()) && (letter == binaryLetter[i])) {
			norrisLetter += "0";
			i++;
		}
		if (i != binaryLetter.size()) {
			norrisLetter += " ";
		}
	}

	return norrisLetter;
}

int main()
{

	string MESSAGE;
	getline(cin, MESSAGE);
	int i = 0;
	string result = "";
	string binaryResult = "";
	while (i<MESSAGE.size())
	{
		string binaryLetter = "";
		// Convertir lettres en binaire
		binaryResult += letterToBinary(MESSAGE[i]);
		i++;
	}

	// Convertir binaire en Chuck Norris
	result = chuckNorris(binaryResult);



	cout << result << endl;




	// Write an action using cout. DON'T FORGET THE "<< endl"
	// To debug: cerr << "Debug messages..." << endl;

}