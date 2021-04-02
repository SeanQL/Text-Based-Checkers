#pragma once
#pragma once
#include <iostream>
#include <array>
#include "Player.h"
#include <iomanip>
#include <string>

using namespace std;

class CheckerBoard {
public:
	//Starting board
	int board[8][8] =
	{	{ -2,  0, -2,  0, -2,  0, -2,  0 },
		{  0, -2,  0, -2,  0, -2,  0, -2 },
		{ -2,  0, -2,  0, -2,  0, -2,  0 },
		{  0,  1,  0,  1,  0,  1,  0,  1 },
		{  1,  0,  1,  0,  1,  0,  1,  0 },
		{  0,  2,  0,  2,  0,  2,  0,  2 },
		{  2,  0,  2,  0,  2,  0,  2,  0 },
		{  0,  2,  0,  2,  0,  2,  0,  2 } };

	// variables that depending on whose turn initializes to the players and opponents values
	int playerPiece, playerKing, opposingPiece, opposingKing, pickedPiece;

	// constant variables determine moveset
	const static int moveUp = -1, moveDown = 1, moveRight = 1, moveLeft = -1;
	const static int leapUp = -2, leapDown = 2, leapRight = 2, leapLeft = -2;

	//Method to print out board replacing numerical values as characters.
	void printBoard() {
		int x, y;
		char c;
		cout << "X |" << setfill('_') << setw(39) << "|" << endl;
		for (x = 0; x < 8; x++) {
			cout << x + 1 << " ";
			for (y = 0; y < 8; y++) {
				switch (board[x][y]) {
				case 0:
					c = ' ';
					break;
				case 1:
					c = '-';
					break;
				case 2:
					c = 'w';
					break;
				case 3:
					c = 'W';
					break;
				case -2:
					c = 'b';
					break;
				case -3:
					c = 'B';
					break;
				}
				cout << setfill(' ') << "|" << setw(2) << c;
				cout << setfill(' ') << setw(2) << "|";
			}
			cout << endl;
		}
		if (y == 8) {
			cout << "  |" << setfill('_') << setw(39) << "|" << endl;
			cout << "  | 1 || 2 || 3 || 4 || 5 || 6 || 7 || 8 | Y\n";
		}
	}

	//Method for taking turn picking a piece.
	void PickPiece(Player player1, Player player2, int turn) {
		Player movingPlayer, opposingPlayer;

		turn = (turn) % 2;			// Turn determines who gets to pick a piece.

		int x, y = 0;

		// sets who is the moving player, opposing player, and defines their pieces.
		if (turn == 1) {
			movingPlayer = player1;
			playerPiece = 2;
			playerKing = 3;
			opposingPlayer = player2;
			opposingPiece = -2;
			opposingKing = -3;
		}
		if (turn == 0) {
			movingPlayer = player2;
			playerPiece = -2;
			playerKing = -3;
			opposingPlayer = player1;
			opposingPiece = 2;
			opposingKing = 3;
		}

		//  Moving player picks their piece
	Pick:
		cout << movingPlayer.getName() << " pick your piece[X][Y].\n";

		// if x or y have invalid inputs goes to Pick.
		cout << "X: ";
		cin >> x;
		if (cin.fail() || x < 1 || x > 8) {
			cout << "You did not input a valid number!\n";
			cin.clear();
			cin.ignore();
			goto Pick;
		}

		cout << "Y: ";
		cin >> y;
		if (cin.fail() || y < 1 || y > 8) {
			cout << "You did not input a valid number!\n";
			cin.clear();
			cin.ignore();
			goto Pick;
		}
		x--;
		y--;

		// if input picked does not match Moving Player piece or King goes back to Pick
		if (board[x][y] != playerPiece && board[x][y] != playerKing) {
			cout << ("You didn't pick a piece that belongs to you! \n Try Again.\n");
			goto Pick;
		}
		pickedPiece = board[x][y];

		//Depending the piece that's been picked determines moveset
		PlayerMove(movingPlayer, opposingPlayer, x, y, pickedPiece);
	};

	//Player's moves set
	void PlayerMove(Player movingPlayer, Player opposingPlayer, int x, int y, int pickedPiece) {
		char c;
		int leaps = 0;
		int moveUpOrDown, leapUpOrDown, moveLeftOrRight, leapLeftOrRight;

	Move:
		//determines which direction a regular piece goes moves or leaps depending on who it belongs too
		if (pickedPiece == 2) {
			moveUpOrDown = moveUp;
			leapUpOrDown = leapUp;
		}
		else if (pickedPiece == -2) {
			moveUpOrDown = moveDown;
			leapUpOrDown = leapDown;
		}

		//if picked piece is a king gives the option to which vertical movement it can take
		if (pickedPiece == playerKing) {
			cout << "Where would you like to move, up or down? u/d: ";
			cin >> c;
			c = tolower(c);
			if (c != 'u' && c != 'd') {
				cout << "Pick a valid choice.\n";
				cin.clear();
				cin.ignore();
				goto Move;
			}
			if (c == 'u') {
				moveUpOrDown = moveUp;
				leapUpOrDown = leapUp;
			}
			if (c == 'd') {
				moveUpOrDown = moveDown;
				leapUpOrDown = leapDown;
			}
		};

		// moves piece picked right or left
		cout << "Where would you like to move, left or right? l/r: ";
		cin >> c;
		c = tolower(c);

		//if invalid choice goes back to Move
		if (c != 'l' && c != 'r') {
			cout << "Pick a valid choice.\n";
			cin.clear();
			cin.ignore();
			goto Move;
		}

		//sets picked piece to 1 value making it a empty space on the board
		board[x][y] = 1;

		//determines whether the piece will be moving or leaping in a direction
		if (c == 'l') {
			moveLeftOrRight = moveLeft;
			leapLeftOrRight = leapLeft;
		}
		if (c == 'r') {
			moveLeftOrRight = moveRight;
			leapLeftOrRight = leapRight;
		}

		//Determines whether the move is out of bounds or if the space is occupied.
		if (MoveOutOfBounds(x, y, moveUpOrDown, moveLeftOrRight)) {
			cout << "Can't move in that direction, out of bounds.\n";
			goto Move;
		}
		else if (SpaceOccupied(x, y, moveUpOrDown, moveLeftOrRight, playerPiece, playerKing)) {
			cout << "Can't move in that direction, space is occupied.\n";
			goto Move;
		}

		//looks to see if their is a opposing piece to potentially jump over
		else if (SpaceOccupied(x, y, moveUpOrDown, moveLeftOrRight, opposingPiece, opposingKing)) {
			//Determines whether the leap is out of bounds or if the space is occupied.
			if (MoveOutOfBounds(x, y, leapUpOrDown, leapLeftOrRight)) {
				cout << "Can't move in that direction, out of bounds.\n";
				goto Move;
			}
			if (SpaceOccupied(x, y, leapUpOrDown, leapLeftOrRight, playerPiece, playerKing) || SpaceOccupied(x, y, leapUpOrDown, leapLeftOrRight, opposingPiece, opposingKing)) {
				cout << "Can't move in that direction, space is occupied.\n";
				goto Move;
			}

			// Leaps over oppsing piece setting its value to 1
			cout << movingPlayer.getName() << " has moved from [" << x + 1 << "][" << y + 1 << "]";
			cout << " to [" << x + leapUpOrDown + 1 << "][" << y + leapLeftOrRight + 1 << "],";
			cout << " to take " << opposingPlayer.getName() << "'s piece at [" << x + moveUpOrDown + 1 << "][" << y + moveLeftOrRight + 1 << "].\n";

			board[x + moveUpOrDown][y + moveLeftOrRight] = 1;

			//makes the leap over opposing piece
			x += leapUpOrDown;
			y += leapLeftOrRight;
			board[x][y] = pickedPiece;

			//looks for additional opposing pieces to jump over in all directions
			if (SpaceOccupied(x, y, moveUp, moveLeft, opposingPiece, opposingKing) || SpaceOccupied(x, y, moveUp, moveRight, opposingPiece, opposingKing) ||
				SpaceOccupied(x, y, moveDown, moveLeft, opposingPiece, opposingKing) || SpaceOccupied(x, y, moveDown, moveRight, opposingPiece, opposingKing)) {
				
				printBoard();
			Pick:
				// option to move again after leap
				cout << "Move again? y/n: ";
				cin >> c;

				if (c != 'y' && c != 'n') {
					cout << "Pick a valid choice.\n";
					cin.clear();
					cin.ignore();
					goto Pick;
				}
				if (c == 'y') {

					cout << "Move again.\n";
					goto Move;
				}
				else {
					goto End;
				}
			}
		}
		else {
			//regular movement option
			cout << movingPlayer.getName() << " has moved from [" << x + 1 << "][" << y + 1 << "]";
			x += moveUpOrDown;
			y += moveLeftOrRight;
			cout << " to [" << x + 1 << "][" << y + 1 << "].\n";
			goto End;
		}
	End:
		//sets space to the value of the moved piece and check if it is kinged
		board[x][y] = pickedPiece;
		KingMe(movingPlayer, y);
	}
	//checks to see if move is out of bounds
	bool MoveOutOfBounds(int x, int y, int moveUpOrDown, int moveLeftOrRight) {
		if (x + moveUpOrDown < 0 || x + moveUpOrDown > 7 || y + moveLeftOrRight < 0 || y + moveLeftOrRight > 7)
			return true;
		else
			return false;
	}
	//checks to see if space is occupied
	bool SpaceOccupied(int x, int y, int moveUpOrDown, int moveLeftOrRight, int piece, int king) {
		if (board[x + moveUpOrDown][y + moveLeftOrRight] == piece || board[x + moveUpOrDown][y + moveLeftOrRight] == king)
			return true;
		else
			return false;
	}

	//method that determines if a piece is to be kinged
	void KingMe(Player player, int y) {
		//checks if a player piece is at its respective end of the board and crowns it
		if (board[0][y] == 2) {
			cout << endl << player.getName() << " has reached the end of the board and crowned piece at [1][" << y + 1 << "].\n";
			board[0][y] = 3;
			cout << "\n  |" << setfill('-') << setw(28) << " HAIL TO THE KING ";
			cout << setfill('-') << setw(13) << "|\n\n";
		}
		if (board[7][y] == -2) {
			cout << endl;
			cout << player.getName() << " has reached the end of the board and crowned piece at [8][" << y + 1 << "].\n";
			board[7][y] = -3;
			cout << "\n  |" << setfill('-') << setw(28) << " HAIL TO THE KING ";
			cout << setfill('-') << setw(13) << "|\n\n";
		}
	}

	//method that checks  for win condition
	void CheckWin(Player player1, Player player2) {
		bool player1WinCondition;
		bool player2WinCondition;

		//checks to see if there are opponents pieces left if not confirms win condition
		for (int x = 0; x < 7; x++) {
			for (int y = 0; y < 7; y++) {
				if (board[x][y] == 2 || board[x][y] == 3) {
					player2WinCondition = false;
					goto Next;
				}
				else {
					player2WinCondition = true;
				}
			}
		}
	Next:
		for (int x = 0; x < 7; x++) {
			for (int y = 0; y < 7; y++) {
				if (board[x][y] == -2 || board[x][y] == -3) {
					player1WinCondition = false;
					goto End;
				}
				else {
					player1WinCondition = true;
				}
			}
		}

		//if win condition has been met announces winner and ends game
		if (player2WinCondition == true) {
			printBoard();
			cout << endl;
			cout << player1.getName() << " has no pieces left on the board.\n";
			cout << player2.getName() << " has won the Game!\n";
			cout << endl;
		}
		if (player1WinCondition == true) {
			printBoard();
			cout << endl;
			cout << player2.getName() << " has no pieces left on the board.\n";
			cout << player1.getName() << " has won the Game!\n";
			cout << endl;
		}
		cout << "Thank you for playing our game!\n";
		cout << "GoodBye!";

		system("pause");
		exit(0);
	End:
		return;
	};
};