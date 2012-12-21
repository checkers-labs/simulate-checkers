// dames.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "string"
#include "ctime"
#include "vector"


using namespace std;

const int nonPlayable=7;
const int playable = 0;
const int playerOne=1;
const int playerTwo=2;
const int playerOneDame=3;
const int playerTwoDame=4;
vector<vector<int> > Moves;

int blocked=0;

//il y a des bordure donc ajouter 2 a size
const int size=10;

int** createBoard(){

	int** tableau=0;
	tableau = new int*[size];
	bool oneOnTwo=false;

	for (int i = 0; i < size; i++){	
		tableau[i] = new int[size];
		for (int j = 0; j < size; j++){
			if(i==0 || i==size-1 || j==0 || j==size-1 ){
				tableau[i][j] = nonPlayable;
			}else if(oneOnTwo && i<4){
				tableau[i][j] = playerTwo;
				oneOnTwo=false;
			}else if(oneOnTwo && i>5){
				tableau[i][j] = playerOne;
				oneOnTwo=false;
			}else if(oneOnTwo){
				tableau[i][j] = playable;
				oneOnTwo=false;
			}else{
				tableau[i][j] = nonPlayable;
				oneOnTwo=true;
			}

		}
		if(tableau[i][1]==nonPlayable && i!=0){
			oneOnTwo=true;
		}else{
			oneOnTwo=false;
		}


	}

	return tableau;

}

//todo savoir quel coup on choisit ensuite.
void takeAgain(int** tableau,int i,int j,int player){
	int opponent;
	int opponentQueen;

	if(player==playerOne || player==playerOneDame ){
		opponent=playerTwo;
		opponentQueen=playerTwoDame;
	}else{
		opponent=playerOne;
		opponentQueen=playerOneDame;
	}

	if(tableau[i-1][j-1]==opponent || tableau[i-1][j-1]==opponentQueen){
		if(tableau[i-2][j-2]==playable){
			tableau[i][j]=playable;
			tableau[i-1][j-1]=playable;
			tableau[i-2][j-2]=player;
			takeAgain(tableau,i-2,j-2,player);
		}
	}else if(tableau[i-1][j+1]==opponent || tableau[i-1][j+1]==opponentQueen){
		if(tableau[i-2][j+2]==playable){
			tableau[i][j]=playable;
			tableau[i-1][j+1]=playable;
			tableau[i-2][j+2]=player;
			takeAgain(tableau,i-2,j+2,player);
		}
	}else if(tableau[i+1][j-1]==opponent || tableau[i+1][j-1]==opponentQueen){
		if(tableau[i+2][j-2]==playable){
			tableau[i][j]=playable;
			tableau[i+1][j-1]=playable;
			tableau[i+2][j-2]=player;
			takeAgain(tableau,i+2,j-2,player);
		}
	}else if(tableau[i+1][j+1]==opponent || tableau[i+1][j+1]==opponentQueen){
		if(tableau[i+2][j+2]==playable){
			tableau[i][j]=playable;
			tableau[i+1][j+1]=playable;
			tableau[i+2][j+2]=player;
			takeAgain(tableau,i+2,j+2,player);
		}
	}
}

bool oneTeamDied (int** tableau){
	bool oneAlive=false;
	bool twoAlive=false;


	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j)
			if(tableau[i][j]==playerOne || tableau[i][j]==playerOneDame){
				oneAlive=true;
			}else if(tableau[i][j]==playerTwo || tableau[i][j]==playerTwoDame){
				twoAlive=true;
			}
			if(oneAlive && twoAlive){
				return true;
			}
	}	

	return false;
}

bool moveRegular(int **tableau,int i,int j,int player,int coup){
	if(tableau[i][j]==playerOne && player==1){
		if(tableau[i-1][j-1]==playable){
			vector<int> move;
			move.push_back(coup);
			move.push_back(i);
			move.push_back(j);
			move.push_back(i-1);
			move.push_back(j-1);
			if(i-1!=1){
				move.push_back(playerOne);	
			}else{
				move.push_back(playerOneDame);
			}	
			Moves.push_back(move);			
		}else if(tableau[i-1][j+1]==playable){
			vector<int> move;
			move.push_back(coup);
			move.push_back(i);
			move.push_back(j);
			move.push_back(i-1);
			move.push_back(j+1);
			if(i-1!=1){
				move.push_back(playerOne);	
			}else{
				move.push_back(playerOneDame);
			}	
			Moves.push_back(move);	
		}else if(tableau[i-1][j-1]==playerTwo || tableau[i-1][j-1]==playerTwoDame){
			if(tableau[i-2][j-2]==playable){
				vector<int> move;
				move.push_back(coup);
				move.push_back(i);
				move.push_back(j);
				move.push_back(i-2);
				move.push_back(j-2);
				move.push_back(i-1);
				move.push_back(j-1);
				if(i-2!=1){
					move.push_back(playerOne);	
				}else{
					move.push_back(playerOneDame);
				}	
				Moves.push_back(move);				
			}
		}else if(tableau[i-1][j+1]==playerTwo || tableau[i-1][j+1]==playerTwoDame){
			if(tableau[i-2][j+2]==playable){
				tableau[i][j]=playable;
				tableau[i-1][j+1]=playable;
				if(i-2!=1){
					tableau[i-1][j+1]=playerOne;	
				}else{
					tableau[i-1][j+1]=playerOneDame;
				}
				takeAgain(tableau,i-2,j+2,playerOne);
				return true;
			}
		}
	}else if(tableau[i][j]==playerTwo  && player==2){
		if(tableau[i+1][j-1]==playable){
			vector<int> move;
			move.push_back(coup);
			move.push_back(i);
			move.push_back(j);
			move.push_back(i+1);
			move.push_back(j-1);
			if(i-1!=1){
				move.push_back(playerTwo);	
			}else{
				move.push_back(playerTwoDame);
			}	
			Moves.push_back(move);	
		}else if(tableau[i+1][j+1]==playable){
			vector<int> move;
			move.push_back(coup);
			move.push_back(i);
			move.push_back(j);
			move.push_back(i+1);
			move.push_back(j+1);
			if(i-1!=1){
				move.push_back(playerTwo);	
			}else{
				move.push_back(playerTwoDame);
			}	
			Moves.push_back(move);
		}else if(tableau[i+1][j-1]==playerOne || tableau[i+1][j-1]==playerOneDame){
			if(tableau[i+2][j-2]==playable){
				tableau[i][j]=playable;
				tableau[i+1][j-1]=playable;						
				if(i+2!=size-2){
					tableau[i+2][j-2]=playerTwo;	
				}else{
					tableau[i+2][j-2]=playerTwoDame;
				}
				takeAgain(tableau,i+2,j-2,playerTwo);
				return true;
			}
		}else if(tableau[i+1][j+1]==playerOne || tableau[i+1][j+1]==playerOneDame){
			if(tableau[i+2][j+2]==playable){
				tableau[i][j]=playable;
				tableau[i+1][j+1]=playable;
				if(i+2!=size-2){
					tableau[i+2][j+2]=playerTwo;	
				}else{
					tableau[i+2][j+2]=playerTwoDame;
				}
				takeAgain(tableau,i+2,j+2,playerTwo);
				return true;
			}
		}
	}
	return false;
}

bool moveQueen(int **tableau,int i,int j,int player){	
	int	playerChekerQueen;
	int	opponentChecker;
	int	opponentCheckerQueen;

	if(player==1){
		playerChekerQueen=playerOneDame;
		opponentChecker =playerTwo;
		opponentCheckerQueen=playerTwoDame;
	}else{
		playerChekerQueen=playerTwoDame;
		opponentChecker =playerOne;
		opponentCheckerQueen=playerOneDame;
	}
	if(tableau[i][j]==playerChekerQueen){
		if(tableau[i-1][j-1]==opponentChecker || tableau[i-1][j-1]==opponentCheckerQueen){
			if(tableau[i-2][j-2]==playable){
				tableau[i][j]=playable;
				tableau[i-1][j-1]=playable;
				tableau[i-2][j-2]=playerChekerQueen;
				takeAgain(tableau,i-2,j-2,playerChekerQueen);
				return true;
			}
		}else if(tableau[i-1][j+1]==opponentChecker || tableau[i-1][j+1]==opponentCheckerQueen){
			if(tableau[i-2][j+2]==playable){
				tableau[i][j]=playable;
				tableau[i-1][j+1]=playable;
				tableau[i-2][j+2]=playerChekerQueen;
				takeAgain(tableau,i-2,j+2,playerChekerQueen);
				return true;
			}
		}else if(tableau[i+1][j-1]==opponentChecker || tableau[i-1][j-1]==opponentCheckerQueen){
			if(tableau[i+2][j-2]==playable){
				tableau[i][j]=playable;
				tableau[i+1][j-1]=playable;
				tableau[i+2][j-2]=playerChekerQueen;
				takeAgain(tableau,i+2,j-2,playerChekerQueen);
				return true;
			}
		}else if(tableau[i+1][j+1]==opponentChecker || tableau[i+1][j+1]==opponentCheckerQueen){
			if(tableau[i+2][j+2]==playable){
				tableau[i][j]=playable;
				tableau[i+1][j+1]=playable;
				tableau[i+2][j+2]=playerChekerQueen;
				takeAgain(tableau,i+2,j+2,playerChekerQueen);
				return true;
			}
		}else if(tableau[i-1][j-1]==playable){
			tableau[i][j]=playable;
			tableau[i-1][j-1]=playerChekerQueen;
			return true;
		}else if(tableau[i+1][j-1]==playable){
			tableau[i][j]=playable;
			tableau[i+1][j-1]=playerChekerQueen;
			return true;
		}else if(tableau[i+1][j+1]==playable){
			tableau[i][j]=playable;
			tableau[i+1][j+1]=playerChekerQueen;
			return true;
		}else if(tableau[i-1][j+1]==playable){
			tableau[i][j]=playable;
			tableau[i-1][j+1]=playerChekerQueen;
			return true;
		}


	}
	return false;
}

void play(int** tableau,int player,int coup){
	bool played;
	for (int i = 0;  i < size; ++i) {
		for (int j = 0; j < size; ++j){			
			played=moveRegular(tableau,i,j,player,coup);
			if(played){
				return;
			}else{
				played=moveQueen(tableau,i,j,player);
				if(played){
					return;
				}
			}
		}
	}	
	blocked++;
	return;

}

int main()
{

	int** tableau = createBoard();
	int i=0;
	int games;
	int nbrFois;
	cin >> games;
	cin >> nbrFois;

	int games2=games;

	while(nbrFois>0){
		clock_t Start = clock();
		games = games2;
		while(games>0){
			while(blocked!=2 && oneTeamDied(tableau) && i<40) {
				blocked=0;
				play(tableau,1,i);
				play(tableau,2,i);
				i++;	
				//int** test= coup[1];
			/*	cout<<"##################\n";

				for (int i = 0; i < size; ++i) {
					for (int j = 0; j < size; ++j)
						cout << test[i][j] << " ";
					cout << endl;
				}*/	

			}
			games--;
		}
		nbrFois--;

		cout << "finit : "<< games2 <<" partie de "<< i <<" tour en "<<(clock()-Start)<< "ms"<<endl;
	}


	cin >> games2;

	return 0;
}