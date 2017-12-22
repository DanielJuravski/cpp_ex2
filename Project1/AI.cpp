#include <iostream>
#include <string>
#include <algorithm>
#include "AI.h"

using namespace std;
#define BOARD_SIZE 5
#define MINIMAX_DEPTH 3

//coordinates of the next move
struct NextMoveCoors
{
	int row, col;
};

//util function. print 2d dynamic arrey
void AI::printBoardToConsule(string **board)
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
			cout << board[i][j];
		cout << endl;
	}
	cout << endl;
}

//util function. print 2d static arrey
void AI::printArreyToConsule(string board[BOARD_SIZE][BOARD_SIZE])
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
			cout << board[i][j];
		cout << endl;
	}
	cout << endl;
}

//Constructor.
AI::AI(string **i_board)
{
	this->board = i_board;
	
	cout << "input:" << endl;
	printBoardToConsule(board);
	cout << "======" << endl;
}


//Check if there are any optional moves on the board.
//True - the board is not full, False - the board is full. 
bool AI::isMovesLeft()
{
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			if (board[i][j] == "E")
				return true;
	return false;
}

//returns number of "B" on the board
int AI::numOfBoardBlacks()
{
	int count = 0;
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			if (board[i][j] == "B")
				count++;
	return count;
}
//returns number of "W" on the board
int AI::numOfBoardWhites()
{
	int count = 0;
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			if (board[i][j] == "W")
				count++;
	return count;
}
//returns number of "B" on the board edges
int AI::numOfEdgeBlacks()
{
	int count = 0;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		if (board[0][i] == "B")
			count++;
		if (board[BOARD_SIZE - 1][i] == "B")
			count++;
		if (board[i][0] == "B")
			count++;
		if (board[i][BOARD_SIZE - 1] == "B")
			count++;
	}

	return count;
}
//returns number of "W" on the board edges
int AI::numOfEdgeWhites()
{
	int count = 0;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		if (board[0][i] == "W")
			count++;
		if (board[BOARD_SIZE - 1][i] == "W")
			count++;
		if (board[i][0] == "W")
			count++;
		if (board[i][BOARD_SIZE - 1] == "W")
			count++;
	}

	return count;
}


//Returns a value based on who is winning
int AI::evaluate()
{
	int h;

	//if game over
	if (!isMovesLeft())
	{
		//black won
		if (numOfBoardBlacks() > numOfBoardWhites())
			return 999;
		//white won
		else //(numOfBoardBlacks() < numOfBoardWhites())
			return -999;
	}
	else
	{
		//tie
		if (numOfBoardBlacks() == numOfBoardWhites())
			return 0;
		else
		{
			//huristic eval
			h = numOfBoardBlacks() - numOfBoardWhites() + numOfEdgeBlacks() - numOfEdgeWhites();
			return h;
		}
	}
}


//after each move, there are points on the board that should switch their color.
void AI::changeBoardColors(int row, int col, string sign)
{
	//for each while loop
	int checkRow;
	int checkCol;
	int i;
	int j;

	//N
	checkRow = row;
	checkCol = col;
	while (checkRow > 0)
	{
		checkRow--;
		if (board[checkRow][checkCol] == sign)
		{
			for (i = row; i > checkRow; i--)
				board[i][checkCol] = sign;
			break;
		}
	}

	//NE
	checkRow = row;
	checkCol = col;
	while (checkRow > 0 && checkCol < BOARD_SIZE-1)
	{
		checkRow--;
		checkCol++;
		if (board[checkRow][checkCol] == sign)
		{
			for (i = row, j = col; i > checkRow && j < checkCol; i--, j++)
				board[i][j] = sign;
			break;
		}
	}

	//E
	checkRow = row;
	checkCol = col;
	while (checkCol < BOARD_SIZE-1)
	{
		checkCol++;
		if (board[checkRow][checkCol] == sign)
		{
			for (j = col; j < checkCol; j++)
				board[checkRow][j] = sign;
			break;
		}
	}

	//SE
	checkRow = row;
	checkCol = col;
	while (checkRow < BOARD_SIZE-1 && checkCol < BOARD_SIZE-1)
	{
		checkRow++;
		checkCol++;
		if (board[checkRow][checkCol] == sign)
		{
			for (i = row, j = col; i < checkRow && j < checkCol; i++, j++)
				board[i][j] = sign;
			break;
		}
	}
	
	//S
	checkRow = row;
	checkCol = col;
	while (checkRow < BOARD_SIZE-1)
	{
		checkRow++;
		if (board[checkRow][checkCol] == sign)
		{
			for (i = col; i < checkRow; i++)
				board[i][checkCol] = sign;
			break;
		}
	}

	//SW
	checkRow = row;
	checkCol = col;
	while (checkRow < BOARD_SIZE-1 && checkCol > 0)
	{
		checkRow++;
		checkCol--;
		if (board[checkRow][checkCol] == sign)
		{
			for (i = row, j = col; i < checkRow && j > checkCol; i++, j--)
				board[i][j] = sign;
			break;
		}
	}

	//W
	checkRow = row;
	checkCol = col;
	while (checkCol > 0)
	{
		checkCol--;
		if (board[checkRow][checkCol] == sign)
		{
			for (j = col; j > checkCol; j--)
				board[checkRow][j] = sign;
			break;
		}
	}

	//NW
	checkRow = row;
	checkCol = col;
	while (checkRow > 0 && checkCol > 0)
	{
		checkRow--;
		checkCol--;
		if (board[checkRow][checkCol] == sign)
		{
			for (i = row, j = col; i > checkRow && j > checkCol; i--, j--)
				board[i][j] = sign;
			break;
		}
	}
}


//check if can put in this point
bool AI::ifLegalPoint(int row, int col)
{
	bool iflegal = false;

	//N
	if (row != 0 && board[row - 1][col] != "E")
		iflegal = true;
	//NE
	if (row != 0 && col != BOARD_SIZE - 1 && board[row - 1][col + 1] != "E")
		iflegal = true;
	//E
	if (col != BOARD_SIZE - 1 && board[row][col + 1] != "E")
		iflegal = true;
	//SE
	if (row != BOARD_SIZE - 1 && col != BOARD_SIZE - 1 && board[row + 1][col + 1] != "E")
		iflegal = true;
	//S
	if (row != BOARD_SIZE - 1 && board[row + 1][col] != "E")
		iflegal = true;
	//SW
	if (row != BOARD_SIZE - 1 && col != 0 && board[row + 1][col - 1] != "E")
		iflegal = true;
	//W
	if (col != 0 && board[row][col - 1] != "E")
		iflegal = true;
	//NW
	if (col != 0 && row != 0 && board[row - 1][col - 1] != "E")
		iflegal = true;

	return iflegal;
}


// This is the minimax function. It considers all
// the possible ways the game can go and returns
// the value of the board
int AI::minimax(int depth, bool isMax)
{
	string tempBoard[BOARD_SIZE][BOARD_SIZE];

	if (depth == 0 || isMovesLeft() == false)
		return evaluate();

	// If this maximizer's move
	if (isMax)
	{
		int best = -1000;

		// Traverse all cells
		for (int i = 0; i<BOARD_SIZE; i++)
		{
			for (int j = 0; j<BOARD_SIZE; j++)
			{
				// Check if cell is empty
				if (board[i][j] == "E")
				{
					if (ifLegalPoint(i, j))
					{
						// Make the move but first save the curr state
						for (int i = 0; i < BOARD_SIZE; i++)
							for (int j = 0; j < BOARD_SIZE; j++)
								tempBoard[i][j] = board[i][j];
						board[i][j] = player;
						changeBoardColors(i, j, player);

						// Call minimax recursively and choose
						// the maximum value
						best = max(best,
							minimax(depth - 1, !isMax));

						// Undo the move
						for (int i = 0; i < BOARD_SIZE; i++)
							for (int j = 0; j < BOARD_SIZE; j++)
								board[i][j] = tempBoard[i][j];
					}
				}
			}
		}
		return best;
	}

	// If this minimizer's move
	else
	{
		int best = 1000;

		// Traverse all cells
		for (int i = 0; i<BOARD_SIZE; i++)
		{
			for (int j = 0; j<BOARD_SIZE; j++)
			{
				// Check if cell is empty
				if (board[i][j] == "E")
				{
					if (ifLegalPoint(i, j))
					{
						// Make the move but first save the curr state
						for (int i = 0; i < BOARD_SIZE; i++)
							for (int j = 0; j < BOARD_SIZE; j++)
								tempBoard[i][j] = board[i][j];
						board[i][j] = opponent;
						changeBoardColors(i, j, opponent);

						// Call minimax recursively and choose
						// the minimum value
						best = min(best,
							minimax(depth - 1, !isMax));

						// Undo the move
						for (int i = 0; i < BOARD_SIZE; i++)
							for (int j = 0; j < BOARD_SIZE; j++)
								board[i][j] = tempBoard[i][j];
					}
				}
			}
		}
		return best;
	}
}


// This will play the best possible move for the player, with the 'minimax' help.
void AI::playNextMove(bool nextTurnBlack)
{
	NextMoveCoors bestMove;
	bestMove.row = -1;
	bestMove.col = -1;
	string nextSymbol = nextTurnBlack == true ? "B" : "W"; 
	int bestVal = nextTurnBlack == true  ? -1000 : 1000;
	string tempBoard[BOARD_SIZE][BOARD_SIZE];

	// Traverse all cells, evalutae minimax function for
	// all empty cells. And play the move with optimal value.
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			// Check if cell is empty
			if (board[i][j] == "E")
			{
				if (ifLegalPoint(i, j))
				{
					// Make the move but first save the curr state
					//copy board to temp board
					for (int i = 0; i < BOARD_SIZE; i++)
						for (int j = 0; j < BOARD_SIZE; j++)
							tempBoard[i][j] = board[i][j];
					board[i][j] = nextSymbol;
					changeBoardColors(i, j, nextSymbol);

					// compute evaluation function for this
					// move.
					int moveVal = minimax(MINIMAX_DEPTH, !nextTurnBlack); //

					// Undo the move
					for (int i = 0; i < BOARD_SIZE; i++)
						for (int j = 0; j < BOARD_SIZE; j++)
							board[i][j] = tempBoard[i][j];

					// If the value of the current move is
					// more than the best value, then update
					// best value
					if (nextTurnBlack == true)
					{
						if (moveVal > bestVal)
						{
							bestMove.row = i;
							bestMove.col = j;
							bestVal = moveVal;
						}
					}
					else
						if (moveVal < bestVal)
						{
							bestMove.row = i;
							bestMove.col = j;
							bestVal = moveVal;
						}
				}
			}
		}
	}

	//finally play the best move. 
	board[bestMove.row][bestMove.col] = nextSymbol;
	changeBoardColors(bestMove.row, bestMove.col, nextSymbol);
}

//start start the best moves for each player until the board is full
string AI::playGame()
{
	bool nextMoveBlack = true;
	while (isMovesLeft())
	{
		playNextMove(nextMoveBlack);
		nextMoveBlack = !nextMoveBlack;
		printBoardToConsule(board);
	}
	
	//see who won and return the winner
	return numOfBoardBlacks() > numOfBoardWhites() ? "B" : "W";
}


AI::~AI()
{
}


