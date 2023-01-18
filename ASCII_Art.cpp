#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
 
 
int nbletter(char a)
{
    if(a-'A'>=0 && a-'A'<26)
    {
        return a-'A';
    }
    else if(a-'a'>=0 && a-'a'<26)
    {
        return a-'a';
    }
    else
    {
        return 26;
    }
}

int main()
{
    int L;
    cin >> L; cin.ignore();
    int H;
    cin >> H; cin.ignore();
    string T;
    getline(cin, T);
    int taille=T.size();
    int tab[taille];
    for(int i=0;i<taille;i++)
    {
        tab[i]=nbletter(T[i]);
    }
    
    for (int i = 0; i < H; i++) {
        string ROW;
        getline(cin, ROW);
        for(int j=0;j<taille;j++)
        {
            int ind=tab[j];
            int debut=ind*L;
            int fin=debut+L;
            for(int k=debut;k<fin;k++)
            {
                cout<<ROW[k];
            }
        }
        cout<<endl;
    }
    
    

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    //cout << "answer" << endl;
}