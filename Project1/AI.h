#include <iostream>
#include <string>
#include <algorithm>

using namespace std;
#define BOARD_SIZE 5

//The class is find the expected winner of the 'reversi' game,
//with the minimax algorithm.
//The class gets 5*5 board at some game situation, and play the until the game is over.
class AI
{
public:
	//Constructor.
	AI(string **board);

	//start start the best moves for each player until the board is full
	string playGame();

	//Destructor
	~AI();

private:
	string **board;
	string player = "B", opponent = "W";

	//Check if there are any optional moves on the board.
	//True - the board is not full, False - the board is full. 
	bool isMovesLeft();

	//returns number of "B" on the board
	int numOfBoardBlacks();
	//returns number of "W" on the board
	int numOfBoardWhites();
	//returns number of "B" on the board edges
	int numOfEdgeBlacks();
	//returns number of "W" on the board edges
	int numOfEdgeWhites();

	// This will play the best possible move for the player, with the 'minimax' help.
	void playNextMove(bool nextTurnBlack);

	//Returns a value based on who is winning
	int evaluate();

	// This is the minimax function. It considers all
	// the possible ways the game can go and returns
	// the value of the board
	int minimax(int depth, bool isMax);

	//after each move, there are points on the board that should switch their color.
	void changeBoardColors(int row, int col, string sign);

	//check if can put in this point
	bool ifLegalPoint(int row, int col);

	//util function. print 2d dynamic arrey
	void printBoardToConsule(string **board);
	//util function. print 2d static arrey
	void printArreyToConsule(string board[BOARD_SIZE][BOARD_SIZE]);
};

