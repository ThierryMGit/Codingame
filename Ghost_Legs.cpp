#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
 
struct space {
     string value;
     bool visited;
 };
 
 bool isConnector(const std::string& s)
 {
     return (s == "-" || s == "|");
 }
 
 string getResult(vector<vector<space>> board, int height, int width, int maxW, int maxH)
 {
     //string val =  board[height][width].value;
     //cerr<< "Evaluation : "<<height<<"/"<<width<<" "<<val<<endl;
     
             if (!isConnector(board[height][width].value)){
             return board[height][width].value;
         }
         board[height][width].visited = true;
         
         //Gauche
         if (width > 0 && board[height][width - 1].value != " " && !board[height][width - 1].visited) {
             //cerr<< "Gauche : "<<height<<"/"<<width - 1<<" "<<board[height][width - 1].value<<endl;
             return getResult(board, height, width - 1, maxW, maxH);
         }
         //Droite
         if (width < maxW && board[height][width + 1].value != " " && !board[height][width + 1].visited) {
             //cerr<< "Droite : "<<height<<"/"<<width + 1<<" "<<board[height][width + 1].value<<endl;
             return getResult(board, height, width + 1, maxW, maxH);
         }
         if (height < maxH && board[height + 1][width].value != " " && !board[height + 1][width].visited) {
             //cerr<< "Bas : "<<height + 1<<"/"<<width<<" "<<board[height + 1][width].value<<endl;
             return getResult(board, height + 1, width, maxW, maxH);
         }
 }
 
int main()
{
    int W;
    int H;
    cin >> W >> H; cin.ignore();
    
    int max = H - 1;
    
    vector<vector<space>> board;
    
    for (int i = 0; i < H; i++) {
        string l;
        getline(cin, l);
        cerr << l << endl;
        vector<space> line;
        for(int j = 0; j < l.length() ; j++) {
            line.push_back({.value = string(1,l[j]),
                                 .visited = false});
        }
        board.push_back(line);
    }
    
    for(int i = 0; i < 1 ; i++) {
        for(int j = 0 ; j < board[i].size() ; j++){
            //cerr <<i<<"/"<<j<<endl;
            if (board[i][j].value != " ") {
                cout << board[i][j].value << getResult(board, i+1,j, W-1, H-1)<<endl;
            }
        }
    }
}