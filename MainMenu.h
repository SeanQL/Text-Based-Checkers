#pragma once

// ProjectTest.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include "Player.h"
#include "Board.h"
#include "string"
#include <array>
using namespace std;
string PlayerOne;

void initiateGame() {
	//addding a comment
	//comment number 2
	//comment 214235636
	cout << "Hello welcome to our Chess Game!\n";
	Player player1;
	Player player2;

	string playerName;
	char option;

	bool pass = false;
	START:
		cout << "Please enter P to play or Q to quit\n";
		cin >> option;
		option = tolower(option);
		//This will initialize the game
		if (option == 'p') {
			cout << "Please select a Username for Player One: ";
			cin >> playerName;
			player1.setName(playerName);
			cout << "Player One has selected " << playerName << " as their Username\n" << endl;

			cout << "Please select a Username for Player Two: ";
			cin >> playerName;
			player2.setName(playerName);
			cout << "Player Two has selected " << playerName << " as their Username\n" << endl;
		}
		else if (option == 'q') {
			//This will close the program
			cout << "Quitting Game";
			system("pause");
			exit(0);
		}
		else {
			cout << "Please choose a proper choice" << endl;
			goto START;
		}

		//This is when the game will start with player one goes first
		cout << "Welcome Players.\n" << endl;
		cout << player1.getName() << " will go First\n";

	CheckerBoard checkerBoard;

	for (int turn = 1; turn <= 50; turn++) {
		checkerBoard.printBoard();
		cout << endl;
		cout << "Turn " << turn << ": ";
		checkerBoard.PickPiece(player1, player2, turn);
		checkerBoard.CheckWin(player1, player2);

		if (turn == 50) {
			cout << "It's a Tie!";
		}
	}
	system("pause");
}

