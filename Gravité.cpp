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
    int width;
    int height;
    cin >> width >> height; cin.ignore();
    int nbsharp[width]={0};
    for (int i = 0; i < height; i++) {
        string line;
        cin >> line; cin.ignore();
        for(int j=0;j<line.length();j++){
            if(line[j]=='#'){
                nbsharp[j]++;
            }
        }
    }
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
         if(nbsharp[j]>=height-i){
          cout<<"#";   
         }
         else{
          cout<<".";   
         }
        }
        cout<<endl;
    }
}