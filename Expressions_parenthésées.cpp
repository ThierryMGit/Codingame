#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    string expression;
    cin >> expression; cin.ignore();
    int par,cro,acc;
    par=cro=acc=0;
    for(int i=0;i<expression.length();i++){
        if((expression[i]=='{') || (expression[i]=='}')) {
            acc++;
        }
          if((expression[i]=='(') || (expression[i]==')')) {
            par++;
        }
          if((expression[i]=='[') || (expression[i]==']')) {
            cro++;
        }
    }

    if((acc%2==0) && (par%2==0) && (cro%2==0)){
        cout << "true" << endl;
    }
    else{
        cout << "false" << endl;
    }
}