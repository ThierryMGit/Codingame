#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int LX; // the X position of the light of power
    int LY; // the Y position of the light of power
    int TX; // Thor's starting X position
    int TY; // Thor's starting Y position
    cin >> LX >> LY >> TX >> TY; cin.ignore();
    

    // game loop
    while (1) {
        int E; // The level of Thor's remaining energy, representing the number of moves he can still make.
        cin >> E; cin.ignore();

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        
            if(TX==LX && TY<LY)
            {
                cout<<"S"<<endl;
                TY++;
            }
            else if(TX==LX && TY>LY)
            {
                cout<<"N"<<endl;
                TY--;
            }
            else if(TX<LX && TY==LY)
            {
                cout<<"E"<<endl;
                TX++;
            }
            else if(TX>LX && TY==LY)
            {
                cout<<"W"<<endl;
                TX--;
            }
            
            else if(TX<LX && TY<LY)
            {
                cout<<"SE"<<endl;
                TX++;
                TY++;
            }
            else if(TX>LX && TY<LY)
            {
                cout<<"SW"<<endl;
                TX--;
                TY++;
            }
            else if(TX<LX && TY>LY)
            {
                cout<<"NE"<<endl;
                TX++;
                TY--;
            }
            else if(TX>LX && TY>LY)
            {
                cout<<"NW"<<endl;
                TX--;
                TY--;
            }
            
            
        
    }
}