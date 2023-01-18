#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#pragma GCC optimize "-O3"


using namespace std;

int boardHeight = 12;
int boardWidth = 6;
int colorBlockScore = 1;
int deathBlockScore = 2;


struct Block
{
    int top;
    int bottom;
};

struct BlockCoord
{
    int horizontal;
    int vertical;
};





void debugBlock(BlockCoord block, vector<int> board[]) {

	cerr << "x : " << block.horizontal << " / y : " << block.vertical <<" / color :"<<board[block.horizontal][block.vertical] <<endl;
}

void debugBlockToDestroy(vector<BlockCoord> blockToDestroyCoords, vector<int> board[])
{

	for (int i = 0; i < blockToDestroyCoords.size(); i++)
	{
		struct BlockCoord coord = blockToDestroyCoords[i];
		debugBlock(coord, board);
	}
}

void debugBoard(vector<int> board[]) {


	for (int i = 0; i < boardHeight; i++) {
		for (int j = 0; j < boardWidth; j++) {
			cerr << board[j][i]<<",";

		}
		cerr << endl;
	}

}

void initHeight(int hId[]) {
	for (int i = 0; i < boardWidth; i++) {
		hId[i] = boardHeight;
	}
}

bool sameBlockCoord(struct BlockCoord block1, struct BlockCoord block2)
{

    return ((block1.horizontal == block2.horizontal) && (block1.vertical == block2.vertical));
}




bool alreadyInBlockCoordVector(vector<BlockCoord> blockToDestroyCoords,struct BlockCoord block) {
	bool containsBlock = true;
	int i = 0;
	int taille = blockToDestroyCoords.size();
	while ((i < taille) && (!sameBlockCoord(blockToDestroyCoords[i], block)))
	{
		i++;
	}
	if (i == taille)
	{
		containsBlock = false;
	}
	return containsBlock;

}


void detectDeathBlockDestruction(vector<BlockCoord>& blockToDestroyCoords,vector<int> board[], bool columns[]){

	vector<BlockCoord> blockToDestroyTemp;
    for(int i=0;i<blockToDestroyCoords.size();i++){
		BlockCoord currentBlock = blockToDestroyCoords[i];
		// Voisin gauche
		if ((currentBlock.horizontal - 1) >= 0) {
			struct BlockCoord bCoordL; bCoordL.horizontal = currentBlock.horizontal - 1; bCoordL.vertical = currentBlock.vertical;
			//debugBlock(bCoordL, board);
			if ((board[bCoordL.horizontal][bCoordL.vertical] == 0) && (!alreadyInBlockCoordVector(blockToDestroyTemp, bCoordL))) {
				blockToDestroyTemp.push_back(bCoordL);
				columns[bCoordL.horizontal] = true;
			}
		}
		// Voisin droite
		if ((currentBlock.horizontal + 1) < boardWidth) {
			struct BlockCoord bCoordR; bCoordR.horizontal = currentBlock.horizontal + 1; bCoordR.vertical = currentBlock.vertical;
			//debugBlock(bCoordR, board);
			if ((board[bCoordR.horizontal][bCoordR.vertical] == 0) && (!alreadyInBlockCoordVector(blockToDestroyTemp, bCoordR))) {
				blockToDestroyTemp.push_back(bCoordR);
				columns[bCoordR.horizontal] = true;
			}
		}
		// Voisin haut
		if ((currentBlock.vertical - 1) >= 0) {
			struct BlockCoord bCoordU; bCoordU.horizontal = currentBlock.horizontal; bCoordU.vertical = currentBlock.vertical - 1;
			//debugBlock(bCoordU, board);
			if ((board[bCoordU.horizontal][bCoordU.vertical] == 0) && (!alreadyInBlockCoordVector(blockToDestroyTemp, bCoordU))) {
				blockToDestroyTemp.push_back(bCoordU);
				columns[bCoordU.horizontal] = true;
			}
		}
		// Voisin bas
		if ((currentBlock.vertical + 1) < boardHeight) {
			struct BlockCoord bCoordD; bCoordD.horizontal = currentBlock.horizontal; bCoordD.vertical = currentBlock.vertical + 1;
			//debugBlock(bCoordD, board);
			if ((board[bCoordD.horizontal][bCoordD.vertical] == 0) && (!alreadyInBlockCoordVector(blockToDestroyTemp, bCoordD))) {
				blockToDestroyTemp.push_back(bCoordD);
				columns[bCoordD.horizontal] = true;
			}
		}
    }
	int taille = blockToDestroyTemp.size();
	for (int l = 0; l < taille; l++) {
		blockToDestroyCoords.push_back(blockToDestroyTemp[l]);
	}

}

vector<BlockCoord>  getBlockToDestroy(vector<int> board[], bool columns[], int hId[]) {

	vector<BlockCoord> blockToDestroyCoords;
	vector<BlockCoord> blockAlreadySeen;
	queue<BlockCoord> blockQueue;
	vector<BlockCoord> blockToDestroyTemp;
	for (int i = 0; i < 6; i++) {
		if (columns[i]) {
			for (int j = hId[i]; j < boardHeight; j++) {
				BlockCoord bCoord;
				bCoord.horizontal = i;
				bCoord.vertical = j;
				if ( (board[i][j] != 0) && (board[i][j] != -2) && (!alreadyInBlockCoordVector(blockAlreadySeen,bCoord)) ){ // Si pas tête de mort
					blockQueue.push(bCoord);
					//cerr << " Block source " << bCoord.horizontal << " / " << bCoord.vertical << " , couleur " << board[bCoord.horizontal][bCoord.vertical] << endl;
					while (!blockQueue.empty()) {
						BlockCoord currentBlock = blockQueue.front();
						blockQueue.pop();
						blockAlreadySeen.push_back(currentBlock);
						//cerr << " Block file " << currentBlock.horizontal << " / " << currentBlock.vertical << " , couleur " << board[currentBlock.horizontal][currentBlock.vertical] << endl;
						//cerr << endl;
						vector<BlockCoord> currentBlockNeighbors;
						// Voisin gauche
						if ((currentBlock.horizontal - 1) >= 0) {
							struct BlockCoord bCoordL; bCoordL.horizontal = currentBlock.horizontal - 1; bCoordL.vertical = currentBlock.vertical; currentBlockNeighbors.push_back(bCoordL);
						}
						// Voisin droite
						if ((currentBlock.horizontal + 1) < boardWidth) {
							struct BlockCoord bCoordR; bCoordR.horizontal = currentBlock.horizontal + 1; bCoordR.vertical = currentBlock.vertical; currentBlockNeighbors.push_back(bCoordR);
						}
						// Voisin haut
						if ((currentBlock.vertical - 1) >= 0) {
							struct BlockCoord bCoordU; bCoordU.horizontal = currentBlock.horizontal; bCoordU.vertical = currentBlock.vertical - 1; currentBlockNeighbors.push_back(bCoordU);
						}
						// Voisin bas
						if ((currentBlock.vertical + 1) < boardHeight ) {
							struct BlockCoord bCoordD; bCoordD.horizontal = currentBlock.horizontal; bCoordD.vertical = currentBlock.vertical + 1; currentBlockNeighbors.push_back(bCoordD);
						}
						//cerr << "Voisins" << endl;
						for (int x = 0; x < currentBlockNeighbors.size(); x++) {
							BlockCoord neighbor = currentBlockNeighbors[x];
							//cerr << " Block " << neighbor.horizontal << " / " << neighbor.vertical << " , couleur " << board[neighbor.horizontal][neighbor.vertical] << endl;
							if ( (board[currentBlock.horizontal][currentBlock.vertical] == board[neighbor.horizontal][neighbor.vertical]) && (!alreadyInBlockCoordVector(blockToDestroyTemp,neighbor)) ) {
								blockQueue.push(neighbor);
								blockToDestroyTemp.push_back(neighbor);
							}
						}
						//cerr << endl;
					}
					int taille = blockToDestroyTemp.size();
					if (taille >= 4) {
						for (int l = 0; l < taille; l++) {
							BlockCoord block = blockToDestroyTemp[l];
							if (!alreadyInBlockCoordVector(blockToDestroyCoords, block)) {
								columns[block.horizontal] = true;								
								blockToDestroyCoords.push_back(block);
							}
							
						}
					}
					blockToDestroyTemp.clear();
				}
			}
		}

	}

	detectDeathBlockDestruction(blockToDestroyCoords, board,columns);


	return blockToDestroyCoords;
}

void getHeight(vector<int> board[], int HId[]) {

	for (int i = 0; i < boardWidth; i++) {
		int j = 11;
		while ((j >= 0) && (board[i][j] != -2)) {
			HId[i] -= 1;
			j--;
		}
		//cerr << "H[" << i << "]" << HId[i] << endl;
	}
}

int getScore(vector<BlockCoord> blockToDestroyCoords,vector<int> board[])
{
    int score=0;
    for(int i=0; i<blockToDestroyCoords.size(); i++)
    {
        BlockCoord bCoord=blockToDestroyCoords[i];
        if(board[bCoord.horizontal][bCoord.vertical]>0){
           score+=colorBlockScore;
        }

       if(board[bCoord.horizontal][bCoord.vertical]==0){
           score+=deathBlockScore;
        }
    }
    return score;
}

void correctBoard(vector<int> board[], bool columns[6], vector<BlockCoord> blockToDestroyCoords) {


	for (int i = 0; i < blockToDestroyCoords.size(); i++) {
		BlockCoord bCoord = blockToDestroyCoords[i];
		board[bCoord.horizontal][bCoord.vertical] = -2;
	}


	for (int i = 0; i < boardWidth; i++) {
		int nb = boardHeight - 1;
		if (columns[i]) {
			for (int j = boardHeight - 1; j >= 0; j--) {
				if (board[i][j] != -2) {
					if (nb != j) {
						board[i][nb] = board[i][j];
						board[i][j] = -2;
					}
					nb--;
				}

			}
		}
		
	}
}

int evalBlock(vector<int> copyBoard[], int hId[], struct Block p, int column)
{
	int nbphase = 1;
	/*
    //*** copie board
    vector<int> copyBoard[boardWidth];
    for (int i = 0; i < boardWidth; i++)
    {
        vector<int> colvec;
        for (int j = 0; j < boardHeight; j++)
        {
            //cerr << board[i][j] << endl;
            colvec.push_back(board[i][j]);
        }
        copyBoard[i] = colvec;
    }
	*/
    //*** avoir hauteur de column
	hId[column] -= 2;
    int height = hId[column];

    // Placement du block dans la colonne column
    int hTop = height;
    int hBottom = height + 1;
    copyBoard[column][hTop] = p.top;
    copyBoard[column][hBottom] = p.bottom;

    //****** Construire le nouveau board

	// Colonnes concernées par l'ajout ou destruction de blocks
	bool columns[6] = { false };
	columns[column] = true;

    //*** Récupérer les blocks détruits ?
    vector<BlockCoord> blockToDestroyCoords=getBlockToDestroy(copyBoard,columns,hId);


    //cerr << "Blocks a detruire en tout  " << endl;
    //debugBlockToDestroy(blockToDestroyCoords, copyBoard);


    // Calculer score en fonction des blocks détruits et modifier les cases détruites en cases vides sur le board copié
    int finalScore=0;
    int score=getScore(blockToDestroyCoords,copyBoard);

	//cerr << "Block dans la colonne "<<column<<endl;

	if (score != 0) {

		finalScore += score;

		//debugBlockToDestroy(blockToDestroyCoords, copyBoard);

		// Correctement placer les blocks sur le board copié
		correctBoard(copyBoard, columns, blockToDestroyCoords);

		//debugBoard(copyBoard);

		// Calculer la height des colonnes
		int copyHId[6];
		initHeight(copyHId);
		getHeight(copyBoard, copyHId);

		//*** Vérifier s'il y a des chaines
		do
		{
			//cerr << "Tour " << nbphase << endl;
			nbphase++;

			// clear blockToDestroyCoords
			blockToDestroyCoords.clear();

			for (int i = 0; i < boardWidth; i++) {
				columns[i] = copyHId[i] < 12 ? true : false;
			}
			blockToDestroyCoords = getBlockToDestroy(copyBoard, columns, copyHId);

			// Calculer score en fonction des blocks détruits et modifier les cases détruites en cases vides sur le board copié
			score= getScore(blockToDestroyCoords, copyBoard);

			if (score != 0) {

				finalScore += score;

				//debugBlockToDestroy(blockToDestroyCoords, copyBoard);

				// Correctement placer les blocks sur le board copié
				correctBoard(copyBoard, columns, blockToDestroyCoords);

				//debugBoard(copyBoard);

				// Calculer la height des colonnes
				int copyHId[6];
				initHeight(copyHId);
				getHeight(copyBoard, copyHId);
			}
		} while (!blockToDestroyCoords.empty());

	}


	//cerr << "Block dans la colonne " << column << " : " << score << endl;

    return finalScore;
}




/*
Méthode meilleure combinaison

*/

int GetBestScore(vector<int> copyBoard[], int hId[], vector<Block> BlockList, int numBlock, int nbBlockTOAnticipate) {

	int scoremax = 0;
	if ( (numBlock == BlockList.size()) || (numBlock == nbBlockTOAnticipate+1) ){
		return 0;
	}
	else {
		// score du block dans la chaque colonne selon le meilleur score des blocs suivants
		//cerr << " Block " << numBlock << endl;
		vector<int> originalBoard[boardWidth];
		for (int i = 0; i < boardWidth; i++) {
			originalBoard[i] = copyBoard[i];
		}

		int copyHId[6];
		for (int i = 0; i < boardWidth; i++) {
			if (hId[i] > 1) {

				int score = 0;
				//debugBoard(copyBoard);
				score = evalBlock(copyBoard, hId, BlockList[numBlock], i);
				//cerr << "score evalBlock : " << score << endl;
				score += GetBestScore(copyBoard, hId, BlockList, numBlock + 1, nbBlockTOAnticipate);
				//cerr << "score getBestScore: " << score << endl;
				scoremax = max(score, scoremax);
				/*if (score > 0) {
				debugBoard(copyBoard);
				}*/
				for (int j = 0; j < boardWidth; j++) {
					copyBoard[j] = originalBoard[j];
				}

				initHeight(hId);
				getHeight(copyBoard, hId);
			}
			
		}
	}
	return scoremax;
}




/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    // game loop
    while (1)
    {

        // Connaitre Index du plus haut block (en prenant en compte le top) de chaque colonne
        int heightId[boardWidth];
        for (int i = 0; i < boardWidth; i++)
        {
            heightId[i] = boardHeight;
        }
        // Stocker les blocks à venir
        vector<Block> BlockList;
        for (int i = 0; i < 8; i++)
        {
            int colorA; // color of the first block
            int colorB; // color of the attached block
            cin >> colorA >> colorB;
            cin.ignore();
            struct Block p;
            p.top = colorA;
            p.bottom = colorB;
            BlockList.push_back(p);
        }

        // Construction du plateau
        vector<int> board[boardWidth];
        for (int i = 0; i < boardHeight; i++)
        {
            string row;
            cin >> row;
            cin.ignore();
            for (int j = 0; j < row.length(); j++)
            {
                board[j].push_back(row[j] - '0');
                if (row[j] != '.')
                {
                    heightId[j]-=1;
                }
            }
        }

        //*** Détermination du meilleur emplacement pour le prochain block

		vector<int> originalBoard[boardWidth];
		for (int i = 0; i < boardWidth; i++) {
			originalBoard[i] = board[i];
		}

        // On garde les colonnes avec le meilleur score
        int cptmax = 0;

        vector<int> columns;
        for (int i = 0; i < boardWidth; i++)
        {
			//cerr << " Colonne " << i << endl;
			if (heightId[i] > 1) {
				int cpt = evalBlock(board, heightId, BlockList[0], i);
				//cerr <<"score evalBlock : " << cpt << endl;
				cpt += GetBestScore(board, heightId, BlockList,1,3);
				//cerr<<"score getBestScore: " << cpt << endl;
				for (int j = 0; j < boardWidth; j++) {
					board[j] = originalBoard[j];
				}
				initHeight(heightId);
				getHeight(board, heightId);
				if (cpt == cptmax)
				{
					cptmax = cpt;
					columns.push_back(i);
				}
				else if ((cpt > cptmax) && (heightId[i]>0))
				{
					cptmax = cpt;
					columns.clear();
					columns.push_back(i);
				}
			}
            
        }


        string column = "";
        int size = columns.size();
		for (int i = 0; i < size; i++) {
			//cerr << "colonne " << columns[i] << endl;
		}
       //cerr << "compteur max : " << cptmax << endl;
        if (size >= 1)
        {
            // Si cptmax <4 on met sur la moins haute / Sinon la plus haute avec height>0
           // if (cptmax <4)
            //{
                int heightmin = heightId[columns[0]];
				//cerr << "hauteur colonne " << columns[0] << " : " << heightmin << endl;
                column = to_string(columns[0]);
                for (int i = 1; i < size; i++)
                {
                    int columnHeight = heightId[columns[i]];
					//cerr << "hauteur colonne " << columns[i] << " : " << columnHeight << endl;
                    if (columnHeight > heightmin)
                    {
                        heightmin = columnHeight;
                        column = to_string(columns[i]);
                    }
                }
            /*}
            else
            {
                int heightmax = heightId[columns[0]];
                column = to_string(columns[0]);
                for (int i = 1; i < size; i++)
                {
                    int columnHeight = heightId[columns[i]];
                    if ( (columnHeight < heightmax) && (heightId[columns[i]]>0))
                    {
                        heightmax = columnHeight;
                        column = to_string(columns[i]);
                    }
                }

            }*/
        }
        else
        {
            column = "0";
        }


        // Plateau de l'adversaire
        for (int i = 0; i < boardHeight; i++)
        {
            string row; // One line of the map ('.' = empty, '0' = skull block, '1' to '5' = colored block)
            cin >> row;
            cin.ignore();
        }




        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        //cerr << "colonne mise  : " << column << endl;
        cout << column << endl; // "x": the column in which to drop your blocks
    }
}
