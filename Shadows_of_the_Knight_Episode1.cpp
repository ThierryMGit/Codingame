#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
 

bool contrarydir(string now,string previous)
{
    return (now=="U" && previous=="D") || (now=="D" && previous=="U") || (now=="L" && previous=="R") || (now=="R" && previous=="L") || (now=="UR" && previous=="DL") || (now=="DL" && previous=="UR") || (now=="UL" && previous=="DR") || (now=="DR" && previous=="UL");
}
 
int middle(int laxe,int l)
{

    return round((float)((max(laxe,l)-min(laxe,l))/2.0f));
}

int getX(int Xcible, int myX,string BOMB_DIR){
	int X0=myX;

	if (BOMB_DIR == "UR")
	{
		X0 = X0 + middle(Xcible, X0);
	}
	if (BOMB_DIR == "R")
	{
		X0 = X0 + middle(Xcible, X0);
	}
	if (BOMB_DIR == "DR")
	{
		X0 = X0 + middle(Xcible, X0);
	}
	if (BOMB_DIR == "DL")
	{
		X0 = X0 - middle(Xcible, X0);
	}
	if (BOMB_DIR == "L")
	{
		X0 = X0 - middle(Xcible, X0);
	}
	if (BOMB_DIR == "UL")
	{
		X0 = X0 - middle(Xcible, X0);
	}
	return X0;
}

int getY(int Ycible, int myY, string BOMB_DIR) {
	int Y0=myY;

	if (BOMB_DIR == "U")
	{
		Y0 = Y0 - middle(Ycible, Y0);
	}
	if (BOMB_DIR == "UR")
	{
		Y0 = Y0 - middle(Ycible, Y0);
	}
	if (BOMB_DIR == "DR")
	{
		Y0 = Y0 + middle(Ycible, Y0);
	}
	if (BOMB_DIR == "D")
	{
		Y0 = Y0 + middle(Ycible, Y0);
	}
	if (BOMB_DIR == "DL")
	{
		Y0 = Y0 + middle(Ycible, Y0);
	}
	if (BOMB_DIR == "UL")
	{
		Y0 = Y0 - middle(Ycible, Y0);
	}
	return Y0;
}
 
int main()
{
    int W; // width of the building.
    int H; // height of the building.
    cin >> W >> H; cin.ignore();
    int N; // maximum number of turns before game over.
    cin >> N; cin.ignore();
    int X0;
    int Y0;
    cin >> X0 >> Y0; cin.ignore();
    double coeff=1.0;
    int ajust = 0;
    string previousdir="";
	bool contrary = false;
	int previousX,previousY,yHaut,yBas,xGauche,xDroite;
	yHaut = 0;
	yBas = H;
	xGauche = 0;
	xDroite = W;
	string dirX = "";
	string dirY = "";
    // game loop
    while (1) {
        string BOMB_DIR; // the direction of the bombs from batman's current location (U, UR, R, DR, D, DL, L or UL)
        cin >> BOMB_DIR; cin.ignore();
        
       /* if(contrarydir(BOMB_DIR,previousdir))
        {
			X0 = getX(previousX, X0, BOMB_DIR);
			Y0 = getY(previousY, Y0, BOMB_DIR);
		}
		else {*/
		previousX = X0;
		previousY = Y0;
			if (BOMB_DIR == "U")
			{
				//if (dirY == "Down") {
					yBas = previousY;
				//}
				Y0 = getY(yHaut, Y0, BOMB_DIR);
				dirY = "Up";
			}
			if (BOMB_DIR == "UR")
			{
				//if (dirY == "Down") {
					yBas = previousY;
				//}
				//if (dirX == "Left") {
					xGauche = previousX;
					//}
				X0 = getX(xDroite, X0, BOMB_DIR);
				Y0 = getY(yHaut, Y0, BOMB_DIR);
				dirY = "Up";
				dirX == "Right";
			}
			if (BOMB_DIR == "R")
			{
				//if (dirX == "Left") {
					xGauche = previousX;
					//}
				X0 = getX(xDroite, X0, BOMB_DIR);
				dirX == "Right";
			}
			if (BOMB_DIR == "DR")
			{
				//if (dirY == "Up") {
					yHaut = previousY;
					//}
					//if (dirX == "Left") {
					xGauche = previousX;
					//}
				X0 = getX(xDroite, X0, BOMB_DIR);
				Y0 = getY(yBas, Y0, BOMB_DIR);
				dirY = "Down";
				dirX == "Right";
			}
			if (BOMB_DIR == "D")
			{
				//if (dirY == "Up") {
					yHaut = previousY;
					//}
				Y0 = getY(yBas, Y0, BOMB_DIR);
				dirY = "Down";
			}
			if (BOMB_DIR == "DL")
			{
				//if (dirY == "Up") {
					yHaut = previousY;
					//}
					//if (dirX == "Right") {
					xDroite = previousX;
					//}
				X0 = getX(xGauche, X0, BOMB_DIR);
				Y0 = getY(yBas, Y0, BOMB_DIR);
				dirY = "Down";
				dirX == "Left";
			}
			if (BOMB_DIR == "L")
			{
				//if (dirX == "Right") {
					xDroite = previousX;
					//}
				X0 = getX(xGauche, X0, BOMB_DIR);
				dirX == "Left";
			}
			if (BOMB_DIR == "UL")
			{
				//if (dirY == "Down") {
					yBas = previousY;
					//}
					//if (dirX == "Right") {
					xDroite = previousX;
					//}
				X0 = getX(xGauche, X0, BOMB_DIR);
				Y0 = getY(yHaut, Y0, BOMB_DIR);
				dirY = "Up";
				dirX == "Left";
			}
			
		//}
       
        previousdir=BOMB_DIR;
        if (X0>=W)
        {
            X0=W-1;
        }
        if(X0<0)
        {
            X0=0;
        }
        if (Y0>=H)
        {
            Y0=H-1;
        }
        if(Y0<0)
        {
            Y0=0;
        }
        cout<<X0<<" "<<Y0<<endl;

		previousX = X0;
		previousY = Y0;
        }
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        //cout << "0 0" << endl; // the location of the next window Batman should jump to.
    }
