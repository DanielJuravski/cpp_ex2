#include <iostream>
#include <string>
#include <algorithm>

using namespace std;
#define BOARD_SIZE 5

class AI
{
public:
	AI(string **board);
	string playGame();
	void printBoardToConsule(string **board);
	void printarreyToConsule(string board[BOARD_SIZE][BOARD_SIZE]);
	~AI();
private:
	string **board;
	string player = "B", opponent = "W";
	bool isMovesLeft();
	int numOfBoardBlacks();
	int numOfBoardWhites();
	int numOfEdgeBlacks();
	int numOfEdgeWhites();
	void playNextMove(bool nextTurnBlack);
	int evaluate();
	int minimax(int depth, bool isMax);
	void changeBoardColors(int row, int col, string sign);
	bool ifLegalPoint(int row, int col);


};

