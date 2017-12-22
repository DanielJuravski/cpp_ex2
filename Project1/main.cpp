#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <stack>
#include <queue>
#include <map>
#include <list>
#include <set>
#include "AI.h"

using namespace std;
#define BOARD_SIZE 5

// Process the input file, returns the 2-D string arrey.
string** processInputFile(ifstream& i_infile)
{
	string **board = NULL;
	string boardLine;

	if (i_infile.is_open())
	{
		board = new string*[BOARD_SIZE];
		for (int i = 0; i < BOARD_SIZE; i++)
			board[i] = new string[BOARD_SIZE];
		int row = 0;
		while (getline(i_infile, boardLine))
		{
			for (int col = 0; col < BOARD_SIZE; col++)
				board[row][col] = boardLine[col];
			row++;
		}
	}
	else
	{
		board = NULL;
	}
	i_infile.close();

	return board;
}


//main function
//Board size is always 5, (defined at head).
int main()
{
	string **board = NULL;
	ifstream file("input.txt");
	board = processInputFile(file);
	AI game(board);
	string winner = game.playGame();

	
	cout << "Winner is: " << winner << endl;

	getchar();
	return 0;
}