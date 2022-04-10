//Amir Anckonina
//Reversi Project May 2021

//Welocome to Reversi game session.
//In the game there are two players, each player recieves discs with the symbol X or O.
//Every game starts with four discs placed in the center of the board, 2 of X and 2 of O.
//player X goes first. and players take turns making moves.
// A move consists of a player placing a disc of his symbol onboard.
// The disc must be placed so as to outflank one or more opponent discs,
// which are then flipped over to the current player's sympbol.
//Outflanking your opponent means to place your disc such that it traps one or more
//of your opponent's discs between another disc of your color along a horizontal, vertical or diagonal line through the board square 
//The game ends if there are no vacant places on board, or all board consist discs of one player only,
//or one of the players doesn't have an option to place a disc..
// The winner is the one with more discs on board.
//Enjoy.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

//Constants for thr arrays
#define ROWS 21
#define COLS 21
#define MAX_NAME_LEN 30

//Functions signatures
int selectBoard();
int setBoardDimensions(int boardChoice);
int setBoard();
void initialCharsInput(char board[][COLS], int boardDimensions);
void printCurrentBoard(char board[][COLS], int boardDimensions);
bool checkEast(char board[][COLS], int boardDimensions, int rowIndexToCheck, int colIndexToCheck, char activeSoldier, char rivalSoldier, char space);
bool checkWest(char board[][COLS], int boardDimensions, int rowIndexToCheck, int colIndexToCheck, char activeSoldier, char rivalSoldier, char space);
bool checkSouth(char board[][COLS], int boardDimensions, int rowIndexToCheck, int colIndexToCheck, char activeSoldier, char rivalSoldier, char space);
bool checkNorth(char board[][COLS], int boardDimensions, int rowIndexToCheck, int colIndexToCheck, char activeSoldier, char rivalSoldier, char space);
bool checkSouthEast(char board[][COLS], int boardDimensions, int rowIndexToCheck, int colIndexToCheck, char activeSoldier, char rivalSoldier, char space);
bool checkSouthWest(char board[][COLS], int boardDimensions, int rowIndexToCheck, int colIndexToCheck, char activeSoldier, char rivalSoldier, char space);
bool checkNorthEast(char board[][COLS], int boardDimensions, int rowIndexToCheck, int colIndexToCheck, char activeSoldier, char rivalSoldier, char space);
bool checkNorthWest(char board[][COLS], int boardDimensions, int rowIndexToCheck, int colIndexToCheck, char activeSoldier, char rivalSoldier, char space);
bool checkVacantPlaceisValid(char board[][COLS], int boardDimensions, int rowIndexToCheck, int colIndexToCheck, char activeSoldier, char rivalSoldier, char space);
bool checkOptionToMove(char board[][COLS], int boardDimensions, char activeSoldier, char rivalSoldier, char space);
bool checkMoveIsValid(char board[][COLS], int boardDimensions, int rowChoice, int colChoice, char activeSoldier, char rivalSoldier, char space);
void flipEast(char board[][COLS], int boardDimensions, int rowChoice, int colChoice, char activeSoldier, char rivalSoldier, char space);
void flipWest(char board[][COLS], int boardDimensions, int rowChoice, int colChoice, char activeSoldier, char rivalSoldier, char space);
void flipSouth(char board[][COLS], int boardDimensions, int rowChoice, int colChoice, char activeSoldier, char rivalSoldier, char space);
void flipNorth(char board[][COLS], int boardDimensions, int rowChoice, int colChoice, char activeSoldier, char rivalSoldier, char space);
void flipSouthEast(char board[][COLS], int boardDimensions, int rowChoice, int colChoice, char activeSoldier, char rivalSoldier, char space);
void flipSouthWest(char board[][COLS], int boardDimensions, int rowChoice, int colChoice, char activeSoldier, char rivalSoldier, char space);
void flipNorthEast(char board[][COLS], int boardDimensions, int rowChoice, int colChoice, char activeSoldier, char rivalSoldier, char space);
void flipNorthWest(char board[][COLS], int boardDimensions, int rowChoice, int colChoice, char activeSoldier, char rivalSoldier, char space);
void updateMoveOnBoard(char board[][COLS], int boardDimensions, int rowChoice, int colChoice, char activeSoldier, char rivalSoldier, char space);
void executeMove(char board[][COLS], int boardDimensions, char activeSoldier, char rivalSoldier, char space);
void printWhoWon(char playerOneName[], char playerTwoName[], int xCounter, int oCounter);
void calcWhoWon(char board[][COLS], int boardDimensions, char playerOneName[], char playerTwoName[], char x, char o);
void fullGameSession(char board[][COLS], int boardDimensions, char playerOneName[], char playerTwoName[]);

//Main fuc including board preparations, name the players input and fullGameSession function.
void main()
{
	char board[ROWS][COLS];
	char playerOneName[MAX_NAME_LEN], playerTwoName[MAX_NAME_LEN];
	int boardDimensions = 0;

	boardDimensions = setBoard();
	if (boardDimensions != 0) //If user choice isn't to Exit
	{
		printf("Enter first player name: ");
		scanf("%s", playerOneName);
		printf("Enter second player name: ");
		scanf("%s", playerTwoName);
		initialCharsInput(board, boardDimensions);
		printCurrentBoard(board, boardDimensions);
		fullGameSession(board, boardDimensions, playerOneName, playerTwoName);
	}
}

//Ask the players to chooseboard dimensions and returning the choice
int selectBoard()
{
	int boardChoice = 0;
	printf("Select board size:\n0. Exit\n1. 10x10\n2. 15x15\n3. 20x20\n");
	scanf("%d", &boardChoice);

	while (boardChoice > 3 || boardChoice < 0)
	{
		printf("Invalid option. \n");
		printf("Select board size: ");
		scanf("%d", &boardChoice);
	}
	return boardChoice;
}

//Recieving the board choice (1,2,3) and returning the dimensions for the the board (i.e. 10X10) 
int setBoardDimensions(int boardChoice)
{
	switch (boardChoice)
	{
	case 1:
		return 10;
	case 2:
		return 15;
	case 3:
		return 20;
	default:
		return 0;
	}
}

//This function will return the actual size of the board. 0 for Exit choice.
int setBoard()
{
	int boardChoice = 0;
	int boardDimensions = 0;

	boardChoice = selectBoard();
	boardDimensions = setBoardDimensions(boardChoice);
	return boardDimensions;
}

//initial variables to the board
void initialCharsInput(char board[][COLS], int boardDimensions)
{
	int row, col;
	char x = 'X';
	char o = 'O';
	char space = '_';
	for (row = 0; row < boardDimensions; row++)
	{
		for (col = 0; col < boardDimensions; col++)
		{
			board[row][col] = space;
		}
	}

	//Place initial soldiers.
	board[(boardDimensions / 2) - 1][(boardDimensions / 2) - 1] = x;
	board[(boardDimensions / 2)][(boardDimensions / 2)] = x;
	board[(boardDimensions / 2) - 1][(boardDimensions / 2)] = o;
	board[(boardDimensions / 2)][(boardDimensions / 2) - 1] = o;
}

//printing currentBoard
void printCurrentBoard(char board[][COLS], int boardDimensions)
{
	{
		int row, col, i;
		int rowOrColIndex = 1;

		printf("   ");
		for (i = 0; i < boardDimensions; i++)
		{
			printf("%3d", rowOrColIndex);
			rowOrColIndex++;
		}
		printf("\n");
		rowOrColIndex = 1;
		for (row = 0; row < boardDimensions; row++)
		{
			printf("%3d", rowOrColIndex);
			for (col = 0; col < boardDimensions; col++)
			{
				printf("%3c", board[row][col]);
			}
			rowOrColIndex++;
			printf("\n");
		}

	}
}

//Recieves a vacant location on board -> returning True/False whether the current player can place a soldier, considering the content on board from the right
bool checkEast(char board[][COLS], int boardDimensions, int rowIndexToCheck, int colIndexToCheck, char activeSoldier, char rivalSoldier, char space)
{
	//REMINDER - only vacant indexes (space) reached this function! In all 8 directions check.
	int colScanner = colIndexToCheck + 2;
	if (board[rowIndexToCheck][colIndexToCheck + 1] == rivalSoldier)
	{
		while (colScanner < boardDimensions) // as long as the scanner didn't reach the border of the board
		{
			if (board[rowIndexToCheck][colScanner] == activeSoldier)
				return true;
			else if (board[rowIndexToCheck][colScanner] == space) //so this direction isn't relevant
				return false;
			else
				colScanner++;
		}
		return false;
	}
	else
		return false;

}

//Recieves a vacant location on board -> returning True/False whether the current player can place a soldier, considering the content on board from the left 
bool checkWest(char board[][COLS], int boardDimensions, int rowIndexToCheck, int colIndexToCheck, char activeSoldier, char rivalSoldier, char space)
{
	int colScanner = colIndexToCheck - 2;
	if (board[rowIndexToCheck][colIndexToCheck - 1] == rivalSoldier)
	{
		while (colScanner >= 0)
		{
			if (board[rowIndexToCheck][colScanner] == activeSoldier)
				return true;
			else if (board[rowIndexToCheck][colScanner] == space)
				return false;
			else
				colScanner--;
		}
		return false;
	}
	else
		return false;
}

//Recieves a vacant location on board -> returning True/False whether the current player can place a soldier, considering the content on board below
bool checkSouth(char board[][COLS], int boardDimensions, int rowIndexToCheck, int colIndexToCheck, char activeSoldier, char rivalSoldier, char space)
{
	int rowScanner = rowIndexToCheck + 2;
	if (board[rowIndexToCheck + 1][colIndexToCheck] == rivalSoldier)
	{
		while (rowScanner < boardDimensions)
		{
			if (board[rowScanner][colIndexToCheck] == activeSoldier)
				return true;
			else if (board[rowScanner][colIndexToCheck] == space)
				return false;
			else
				rowScanner++;
		}
		return false;
	}
	else
		return false;

}

//Recieves a vacant location on board -> returning True/False whether the current player can place a soldier, considering the content on board above
bool checkNorth(char board[][COLS], int boardDimensions, int rowIndexToCheck, int colIndexToCheck, char activeSoldier, char rivalSoldier, char space)
{
	int rowScanner = rowIndexToCheck - 2;
	if (board[rowIndexToCheck - 1][colIndexToCheck] == rivalSoldier)
	{
		while (rowScanner >= 0)
		{
			if (board[rowScanner][colIndexToCheck] == activeSoldier)
				return true;
			else if (board[rowScanner][colIndexToCheck] == space)
				return false;
			else
				rowScanner--;
		}
		return false;
	}
	else
		return false;
}

//Recieves a vacant location on board -> returning True/False whether the current player can place a soldier, considering the content on board on the down right
bool checkSouthEast(char board[][COLS], int boardDimensions, int rowIndexToCheck, int colIndexToCheck, char activeSoldier, char rivalSoldier, char space)
{
	int rowScanner = rowIndexToCheck + 2;
	int colScanner = colIndexToCheck + 2;
	if (board[rowIndexToCheck + 1][colIndexToCheck + 1] == rivalSoldier)
	{
		while (rowScanner < boardDimensions && colScanner < boardDimensions)
		{
			if (board[rowScanner][colScanner] == activeSoldier)
				return true;
			else if (board[rowScanner][colScanner] == space)
				return false;
			else
			{
				rowScanner++;
				colScanner++;
			}
		}
		return false;
	}
	else
		return false;
}

//Recieves a vacant location on board -> returning True/False whether the current player can place a soldier, considering the content on board on the down left
bool checkSouthWest(char board[][COLS], int boardDimensions, int rowIndexToCheck, int colIndexToCheck, char activeSoldier, char rivalSoldier, char space)
{
	int rowScanner = rowIndexToCheck + 2;
	int colScanner = colIndexToCheck - 2;
	if (board[rowIndexToCheck + 1][colIndexToCheck - 1] == rivalSoldier)
	{
		while (rowScanner < boardDimensions && colScanner >= 0)
		{
			if (board[rowScanner][colScanner] == activeSoldier)
				return true;
			else if (board[rowScanner][colScanner] == space)
				return false;
			else
			{
				rowScanner++;
				colScanner--;
			}
		}
		return false;
	}
	else
		return false;
}

//Recieves a vacant location on board -> returning True/False whether the current player can place a soldier, considering the content on board on the up right
bool checkNorthEast(char board[][COLS], int boardDimensions, int rowIndexToCheck, int colIndexToCheck, char activeSoldier, char rivalSoldier, char space)
{
	int rowScanner = rowIndexToCheck - 2;
	int colScanner = colIndexToCheck + 2;
	if (board[rowIndexToCheck - 1][colIndexToCheck + 1] == rivalSoldier)
	{
		while (rowScanner >= 0 && colScanner < boardDimensions)
		{
			if (board[rowScanner][colScanner] == activeSoldier)
				return true;
			else if (board[rowScanner][colScanner] == space)
				return false;
			else
			{
				rowScanner--;
				colScanner++;
			}
		}
		return false;
	}
	else
		return false;
}

//Recieves a vacant location on board -> returning True/False whether the current player can place a soldier, considering the content on board on the up left
bool checkNorthWest(char board[][COLS], int boardDimensions, int rowIndexToCheck, int colIndexToCheck, char activeSoldier, char rivalSoldier, char space)
{
	int rowScanner = rowIndexToCheck - 2;
	int colScanner = colIndexToCheck - 2;
	if (board[rowIndexToCheck - 1][colIndexToCheck - 1] == rivalSoldier)
	{
		while (rowScanner >= 0 && colScanner >= 0)
		{
			if (board[rowScanner][colScanner] == activeSoldier)
				return true;
			else if (board[rowScanner][colScanner] == space)
				return false;
			else
			{
				rowScanner--;
				colScanner--;
			}
		}
		return false;
	}
	else
		return false;
}

//This function recieves a vacant place on board, and the current player. all 8 directions are checked, if necessary, 
//namely, once one of the directions is valid -> returning True, otherwise (non of the 8 functions above is valid -> False)
bool checkVacantPlaceisValid(char board[][COLS], int boardDimensions, int rowIndexToCheck, int colIndexToCheck, char activeSoldier, char rivalSoldier, char space)
{
	bool directionIsValid = false;

	directionIsValid = checkEast(board, boardDimensions, rowIndexToCheck, colIndexToCheck, activeSoldier, rivalSoldier, space);
	if (directionIsValid == true)
		return true;

	directionIsValid = checkWest(board, boardDimensions, rowIndexToCheck, colIndexToCheck, activeSoldier, rivalSoldier, space);
	if (directionIsValid == true)
		return true;

	directionIsValid = checkSouth(board, boardDimensions, rowIndexToCheck, colIndexToCheck, activeSoldier, rivalSoldier, space);
	if (directionIsValid == true)
		return true;

	directionIsValid = checkNorth(board, boardDimensions, rowIndexToCheck, colIndexToCheck, activeSoldier, rivalSoldier, space);
	if (directionIsValid == true)
		return true;

	directionIsValid = checkSouthEast(board, boardDimensions, rowIndexToCheck, colIndexToCheck, activeSoldier, rivalSoldier, space);
	if (directionIsValid == true)
		return true;

	directionIsValid = checkSouthWest(board, boardDimensions, rowIndexToCheck, colIndexToCheck, activeSoldier, rivalSoldier, space);
	if (directionIsValid == true)
		return true;

	directionIsValid = checkNorthEast(board, boardDimensions, rowIndexToCheck, colIndexToCheck, activeSoldier, rivalSoldier, space);
	if (directionIsValid == true)
		return true;

	directionIsValid = checkNorthWest(board, boardDimensions, rowIndexToCheck, colIndexToCheck, activeSoldier, rivalSoldier, space);
	if (directionIsValid == true)
		return true;

	return false;
}

//This function checks if there any option to move for the current player. return Flase if there no options to move
bool checkOptionToMove(char board[][COLS], int boardDimensions, char activeSoldier, char rivalSoldier, char space) //Maybe can scan from the center will run shorter?
{
	int row, col;
	bool vacantPlaceIsValid = false;

	for (row = 0; row < boardDimensions; row++)
	{
		for (col = 0; col < boardDimensions; col++)
		{
			if (board[row][col] == space)
			{
				vacantPlaceIsValid = checkVacantPlaceisValid(board, boardDimensions, row, col, activeSoldier, rivalSoldier, space);
				if (vacantPlaceIsValid == true)
					return true;
			}
		}
	}
	return false;
}

//This function recieves a place that choosed by the player to locate a soldier, and returning True or Flase if the choosed location is Valid
bool checkMoveIsValid(char board[][COLS], int boardDimensions, int rowChoice, int colChoice, char activeSoldier, char rivalSoldier, char space)
{
	bool vacantPlaceIsValid;

	if (board[rowChoice][colChoice] == space)
	{
		vacantPlaceIsValid = checkVacantPlaceisValid(board, boardDimensions, rowChoice, colChoice, activeSoldier, rivalSoldier, space);
		if (vacantPlaceIsValid == true)
			return true;
		else
			return false;
	}
	else
		return false;
}

//This Function flip all relevant rival soldiers on the right side, if there are (only if the direction is valid)
void flipEast(char board[][COLS], int boardDimensions, int rowChoice, int colChoice, char activeSoldier, char rivalSoldier, char space)
{
	bool eastIsValid;
	int colScanner = colChoice + 1;

	eastIsValid = checkEast(board, boardDimensions, rowChoice, colChoice, activeSoldier, rivalSoldier, space);
	if (eastIsValid == true) //update board only if there is an option to flip rival soldiers in this direction.
	{
		while (board[rowChoice][colScanner] != activeSoldier)
		{
			board[rowChoice][colScanner] = activeSoldier;
			colScanner++;
		}
	}
}

//This Function flip all relevant rival soldiers on the left side, if there are (only if the direction is valid)
void flipWest(char board[][COLS], int boardDimensions, int rowChoice, int colChoice, char activeSoldier, char rivalSoldier, char space)
{
	bool westIsValid;
	int colScanner = colChoice - 1;

	westIsValid = checkWest(board, boardDimensions, rowChoice, colChoice, activeSoldier, rivalSoldier, space);
	if (westIsValid == true)
	{
		while (board[rowChoice][colScanner] != activeSoldier)
		{
			board[rowChoice][colScanner] = activeSoldier;
			colScanner--;
		}
	}
}

//This Function flip all relevant rival soldiers below, if there are (only if the direction is valid)
void flipSouth(char board[][COLS], int boardDimensions, int rowChoice, int colChoice, char activeSoldier, char rivalSoldier, char space)
{
	bool southIsValid;
	int rowScanner = rowChoice + 1;

	southIsValid = checkSouth(board, boardDimensions, rowChoice, colChoice, activeSoldier, rivalSoldier, space);
	if (southIsValid == true)
	{
		while (board[rowScanner][colChoice] != activeSoldier)
		{
			board[rowScanner][colChoice] = activeSoldier;
			rowScanner++;
		}
	}
}

//This Function flip all relevant rival soldiers above, if there are (only if the direction is valid)
void flipNorth(char board[][COLS], int boardDimensions, int rowChoice, int colChoice, char activeSoldier, char rivalSoldier, char space)
{
	bool northIsValid;
	int rowScanner = rowChoice - 1;

	northIsValid = checkNorth(board, boardDimensions, rowChoice, colChoice, activeSoldier, rivalSoldier, space);
	if (northIsValid == true)
	{
		while (board[rowScanner][colChoice] != activeSoldier)
		{
			board[rowScanner][colChoice] = activeSoldier;
			rowScanner--;
		}
	}
}

//This Function flip all relevant rival soldiers on down right, if there are (only if the direction is valid)
void flipSouthEast(char board[][COLS], int boardDimensions, int rowChoice, int colChoice, char activeSoldier, char rivalSoldier, char space)
{
	bool southEastIsValid;
	int rowScanner = rowChoice + 1;
	int colScanner = colChoice + 1;

	southEastIsValid = checkSouthEast(board, boardDimensions, rowChoice, colChoice, activeSoldier, rivalSoldier, space);
	if (southEastIsValid == true)
	{
		while (board[rowScanner][colScanner] != activeSoldier)
		{
			board[rowScanner][colScanner] = activeSoldier;
			rowScanner++;
			colScanner++;
		}
	}
}

//This Function flip all relevant rival soldiers down left, if there are (only if the direction is valid)
void flipSouthWest(char board[][COLS], int boardDimensions, int rowChoice, int colChoice, char activeSoldier, char rivalSoldier, char space)
{
	bool southWestIsValid;
	int rowScanner = rowChoice + 1;
	int colScanner = colChoice - 1;

	southWestIsValid = checkSouthWest(board, boardDimensions, rowChoice, colChoice, activeSoldier, rivalSoldier, space);
	if (southWestIsValid == true)
	{
		while (board[rowScanner][colScanner] != activeSoldier)
		{
			board[rowScanner][colScanner] = activeSoldier;
			rowScanner++;
			colScanner--;
		}
	}
}

//This Function flip all relevant rival soldiers up right, if there are (only if the direction is valid)
void flipNorthEast(char board[][COLS], int boardDimensions, int rowChoice, int colChoice, char activeSoldier, char rivalSoldier, char space)
{
	bool northEastIsValid;
	int rowScanner = rowChoice - 1;
	int colScanner = colChoice + 1;

	northEastIsValid = checkNorthEast(board, boardDimensions, rowChoice, colChoice, activeSoldier, rivalSoldier, space);
	if (northEastIsValid == true)
	{
		while (board[rowScanner][colScanner] != activeSoldier)
		{
			board[rowScanner][colScanner] = activeSoldier;
			rowScanner--;
			colScanner++;
		}
	}
}

//This Function flip all relevant rival soldiers up left, if there are (only if the direction is valid)
void flipNorthWest(char board[][COLS], int boardDimensions, int rowChoice, int colChoice, char activeSoldier, char rivalSoldier, char space)
{
	bool northWestIsValid;
	int rowScanner = rowChoice - 1;
	int colScanner = colChoice - 1;

	northWestIsValid = checkNorthWest(board, boardDimensions, rowChoice, colChoice, activeSoldier, rivalSoldier, space);
	if (northWestIsValid == true)
	{
		while (board[rowScanner][colScanner] != activeSoldier)
		{
			board[rowScanner][colScanner] = activeSoldier;
			rowScanner--;
			colScanner--;
		}
	}
}

//This function update current player move on board, calling all 8 possible directions. (flipFunctions...)
void updateMoveOnBoard(char board[][COLS], int boardDimensions, int rowChoice, int colChoice, char activeSoldier, char rivalSoldier, char space)
{
	flipEast(board, boardDimensions, rowChoice, colChoice, activeSoldier, rivalSoldier, space);
	flipWest(board, boardDimensions, rowChoice, colChoice, activeSoldier, rivalSoldier, space);
	flipSouth(board, boardDimensions, rowChoice, colChoice, activeSoldier, rivalSoldier, space);
	flipNorth(board, boardDimensions, rowChoice, colChoice, activeSoldier, rivalSoldier, space);
	flipSouthEast(board, boardDimensions, rowChoice, colChoice, activeSoldier, rivalSoldier, space);
	flipSouthWest(board, boardDimensions, rowChoice, colChoice, activeSoldier, rivalSoldier, space);
	flipNorthEast(board, boardDimensions, rowChoice, colChoice, activeSoldier, rivalSoldier, space);
	flipNorthWest(board, boardDimensions, rowChoice, colChoice, activeSoldier, rivalSoldier, space);

	board[rowChoice][colChoice] = activeSoldier;
	printCurrentBoard(board, boardDimensions);
}

//This function implementing a Move for the current player.
void executeMove(char board[][COLS], int boardDimensions, char activeSoldier, char rivalSoldier, char space)
{
	int rowChoice, colChoice;
	bool validMove = false;

	while (validMove == false)
	{
		printf("Enter your move (row + column): ");
		scanf("%d %d", &rowChoice, &colChoice);
		rowChoice--; //so the row andcol choice will access the right index. i.e.: 1 1 will access [0][0].
		colChoice--;
		validMove = checkMoveIsValid(board, boardDimensions, rowChoice, colChoice, activeSoldier, rivalSoldier, space);
		if (validMove == true)
			updateMoveOnBoard(board, boardDimensions, rowChoice, colChoice, activeSoldier, rivalSoldier, space);
		else
			printf("Invalid Move. \n");
	}
}

//This function recieves the final score and how many soldiers for each player on board, and printing who's the winner
void printWhoWon(char playerOneName[], char playerTwoName[], int xCounter, int oCounter)
{
	printf("The score is\n%s : %d \n%s : %d\n", playerOneName, xCounter, playerTwoName, oCounter);
	if (xCounter > oCounter)
		printf("The Winner of this match is: %s :", playerOneName);
	else if (oCounter > xCounter)
		printf("The Winner of this match is: %s :", playerTwoName);
	else
		printf("It's a draw!");
}

//the following function counting how many soldiers for each player.
void calcWhoWon(char board[][COLS], int boardDimensions, char playerOneName[], char playerTwoName[], char x, char o)
{
	int row, col;
	int xCounter = 0;
	int oCounter = 0;

	for (row = 0; row < boardDimensions; row++)
	{
		for (col = 0; col < boardDimensions; col++)
		{
			if (board[row][col] == x)
				xCounter++;
			else if (board[row][col] == o)
				oCounter++;
		}
	}
	printWhoWon(playerOneName, playerTwoName, xCounter, oCounter);
}

//This function responsible to execute a full game session. checking options to moves, executing move for each player, switching turns and stoped when game over. 
void fullGameSession(char board[][COLS], int boardDimensions, char playerOneName[], char playerTwoName[])
{
	char x = 'X';
	char o = 'O';
	char space = '_';
	bool optionToMoveForX = true;
	bool optionToMoveForO = true;
	bool isPlayerOneTurn = true;
	int rowChoice, colChoice;

	while (optionToMoveForX || optionToMoveForO) //Run game session until both players don't have option to move
	{
		if (isPlayerOneTurn == true)
		{
			optionToMoveForX = checkOptionToMove(board, boardDimensions, x, o, space);
			if (optionToMoveForX == true)
			{
				printf("Player %s (%c) turn \n", playerOneName, x);
				executeMove(board, boardDimensions, x, o, space);
			}
			isPlayerOneTurn = false; //swtich turns
		}
		else //if it's Player2 turn...
		{
			optionToMoveForO = checkOptionToMove(board, boardDimensions, o, x, space);
			if (optionToMoveForO == true)
			{
				printf("Player %s (%c) turn \n", playerTwoName, o);
				executeMove(board, boardDimensions, o, x, space);
			}
			isPlayerOneTurn = true;
		}
	}
	printf("Game Over!\n");
	calcWhoWon(board, boardDimensions, playerOneName, playerTwoName, x, o);
}