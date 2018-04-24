#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

void createBoard(char [5][5]); //this initialises the structure for the game board
void printBoard(const char[5][5]); //prints the game board
void humanMove(char[5][5], int[8], int[9], int&); //allows human player to make a move
void humanPaths(int[8], char[5][5], int, int); //examines the board and adds to the array storing information on the winning paths possible for a human player
void checkWinner(char[5][5], int&); //checks the board to determine if there is a winner
void testMove(int[8], int[8], char[5][5], int, int, int [4], int); //tests all possible moves in order to determine the optimal move for the computer to play
void computerMove(int[8], int[8], char[5][5], int[9], int&); //makes the computer's best move and stores information on which winning paths are open/closed
void initialiseArrays(int[8], int[8], int[9]); //initialises game arrays, for storing information on how close a player is to a win
void testHumMove(char[5][5], int[8], int[8], int&, int, int); //tests the next move a human player can make, part of determining the optimal move for the computer to play

int squares[9]; //global variable, stores information on whether squares have been filled

int main() {
	char board[5][5]; //game board
	int a = 0; //variable passed into functions, reset to 0 if game board is full
	int c = 0; //counter for determining if a game is finished 
	int humanarray[8], computerarray[8]; //these are created to store information on winning paths for computer and human player, there are 8 winning paths in the game
	bool isFull = false; //this shows whether or not the board is full
	
	createBoard(board);
	initialiseArrays(computerarray, humanarray, squares);
	cin.exceptions(ios_base::failbit);

	do {
		c++;
		humanMove(board, humanarray, squares, a);
		checkWinner(board, a);
		if (c < 5) {
			computerMove(computerarray, humanarray, board, squares, a);
		}
		printBoard(board);
		checkWinner(board, a);
		if (a == 0) {
			isFull = true;
		}
	} while (isFull == false);
	
	cout << "Thank you for playing\n";

	return 0;
}

void initialiseArrays(int computerarray[8], int humanarray[8], int squares[9]) { //initialise all arrays with 0 
	for (int i = 0; i < 9; i++) {
		if (i < 8) {
			squares[i] = 0;
			humanarray[i] = 0;
			computerarray[i] = 0;
		}
		else
			squares[i] = 0;
	}
}

void createBoard(char board[5][5]) { //creates empty game board
	for (int i = 0; i < 5; i++) {
		if ((i + 1) % 2 == 1) {
			for (int j = 0; j < 5; j++) {
				if ((j + 1) % 2 == 1) {
					board[i][j] = ' ';
				}
				else if ((j + 1) % 2 == 0) {
					board[i][j] = '|';
				}

			}
		}
		else if ((i + 1) % 2 == 0) {
			for (int j = 0; j < 5; j++) {
				if ((j + 1) % 2 == 1) {
					board[i][j] = '-';
				}
				else if ((j + 1) % 2 == 0) {
					board[i][j] = '+';
				}
			}
		}
	}
	printBoard(board);
}

void printBoard(const char board[5][5]) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cout << board[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

void humanMove(char board[5][5], int humanarray[8], int squares[9], int &a) {
	int move = 0; //accepts number between 1 and 9 corresponding to game squares
	int count = 0; //for checking if square is empty
	do {
		cout << "Please enter an integer between 1 and 9 : ";
		try {
			cin >> move;
		}
		catch (exception e) { //try-catch block asks for an integer if no integer is entered
			cout << "\nYou did not enter an integer\n";
			cin.clear();
			cin.ignore(100, '\n');
			move = 0; 
		}
		if ((move < 1) || (move > 9)) { //asks for integer 1-9 if not input successfully
			cout << "\nPlease pick a move between 1 and 9\n";
		}
		else if ((move >= 1) && (move <= 9)) {
			a = 0;
			count = 0;
			for (int i = 0; i < 5; i += 2) {
				for (int j = 0; j < 5; j += 2) { 
					if (++count == move) { //loop increments along the squares of the tictactoe board using varable count until move == count
						if (squares[count - 1] == 0) { //checks if current square selected is empty
							board[i][j] = 'x'; //places marker
							squares[count - 1]++; //increments in array to indicate square is no longer empty
							humanPaths(humanarray, board, i, j); //adds to the human potential winning paths array
						}
						else if (squares[count - 1] > 0) { //if square is not empty, tells player to move again
							cout << "Invalid move. Please try again\n"; 
							move = 0;
							i = 6; j = 6; //int i and j set outside "for loop" constraints
						}
					}
					if (board[i][j] == ' ') {
						a = 1; //indicates board is not full
					}
				}
			}
		}
	} while ((move < 1) || (move > 9)); //runs loop whilst move is not valid for the game board
}

void humanPaths(int humanarray[8], char board[5][5], int i, int j) {
	switch (board[i][j]) {
	case 'x':
		switch (i) { //increment along the 8 winning conditions, i.e square [0][0] as opening move is on 3 winning paths, increments on humanarray[0], humanarray[3] and humanarray[6]
		case 0:	humanarray[0]++; break; 
		case 2: humanarray[1]++; break;
		case 4: humanarray[2]++; break;
		}
		switch (j) {
		case 0:	humanarray[3]++; break;
		case 2: humanarray[4]++; break;
		case 4: humanarray[5]++; break;
		}
		if (i == j) {
			humanarray[6]++;
		}
		if (i + j == 4) {
			humanarray[7]++;
		}
		break;
	}
}

void checkWinner(char board[5][5], int &a) {
	int countd2 = 0; 
	for (int i = 0; i < 5; i += 2) {
		int counth = 0; //count to see if there are 3 in a row on any horizontal
		int countv = 0; //count to see if there are 3 in a row on any vertical
		int countd = 0; //count to see if there arew 3 in a row on diagonal 1
		for (int j = 0; j < 5; j += 2) { //separate conditions arbitrary values for player 'x' and player 'o' 
			switch (board[i][j]) { 
			case 'x': counth++; break;
			case 'o': counth += 5; break;
			}
			switch (board[j][i]) {
			case 'x': countv++; break;
			case 'o': countv += 5; break;
			}
			switch (board[j][j]) {
			case 'x': countd++; break;
			case 'o': countd += 5; break;
			}
			if (i + j == 4) {
				switch (board[i][j]) {
				case 'x': countd2++; break;
				case 'o': countd2 += 5; break;
				}
			}
			if ((countv == 3) || (counth == 3) || (countd == 3)
				|| (countd2 == 3)) {
				a = 0; i = 6; j = 6; cout << "x wins!!\n";
			} 
			if ((countv == 15) || (counth == 15) || (countd == 15)
				|| (countd2 == 15)) {
				a = 0; i = 6; j = 6; cout << "o wins!!\n";
			}
		}
	}
}

void computerMove(int computerarray[8], int humanarray[8], char board[5][5], int squares[9], int &a) { //makes computer's optimal move
	int move = 0; //variable for storing computer move decision
	int most[4] = { 0, 0, 0, 0 }; //array for storing optimal move and move location
	int count = 0; //variable to cycle through game squares until computer's move is reached
	for (int b = 1; b < 10; b++) {
		move = b;
		count = 0;
		for (int i = 0; i < 5; i += 2) {
			for (int j = 0; j < 5; j += 2) {
				if (++count == move) { //if board position is equal to move position
					if (squares[count - 1] == 0) { //if board position is empty
						testMove(computerarray, humanarray, board, i, j, most, move); //tests move to determine whether it is optimal
					}
					else if (squares[count - 1] > 0) { //if board poosition is not empty
						move = 0;
						i = 6; j = 6; //breaks loop
					}
				}
				if (board[i][j] == ' ') {
					a = 1; //board is not full
				}
			}
		}
	}
	board[most[1]][most[2]] = 'o'; // places mark in optimal position
	squares[most[3] - 1]++; //increments array to show position has been filled
	switch (board[most[1]][most[2]]) {
	case 'o':
		switch (most[1]) { //increments along the 8 winning conditions if satisfied
		case 0:	computerarray[0]++; break;
		case 2: computerarray[1]++; break;
		case 4: computerarray[2]++; break;
		}
		switch (most[2]) {
		case 0:	computerarray[3]++; break;
		case 2: computerarray[4]++; break;
		case 4: computerarray[5]++; break;
		}
		if (most[1] == most[2]) {
			computerarray[6]++;
		}
		if (most[1] + most[2] == 4) {
			computerarray[7]++;
		}
		break;
	}
}

void testMove(int computerarray[8], int humanarray[8], char board[5][5], int i, int j, int most[4], int move) {
	int comarray[8]; //clone arrays showing potential winning paths
	int humarray[8]; //clone arrays showing potential winning paths
	for (int x = 0; x < 8; x++) { //initialisd with data from arrays storing potential winning paths
		comarray[x] = computerarray[x]; 
		humarray[x] = humanarray[x];
	}
	board[i][j] = 'o';
	switch (board[i][j]) { //increment along the 8 winning conditions, i.e square [0][0] is on 3 winning paths, would increment on comarray[0], comarray[3] and comarray[6]
	case 'o':
		switch (i) {
		case 0:	comarray[0]++; break;
		case 2: comarray[1]++; break;
		case 4: comarray[2]++; break;
		}
		switch (j) {
		case 0:	comarray[3]++; break;
		case 2: comarray[4]++; break;
		case 4: comarray[5]++; break;
		}
		if (i == j) {
			comarray[6]++;
		}
		if (i + j == 4) {
			comarray[7]++;
		}
		break;
	}
	
	for (int x = 0; x < 8; x++) { //if winning path occupied by both computer and human, no longer a potential winning path
		if ((comarray[x] > 0) && (humarray[x] > 0)) {
			humarray[x] = -1; comarray[x] = -1;
		}
	}
	int points = 0;

	for (int x = 0; x < 8; x++) { //conditions for selecting optimal move, if either comarray or humarray = 3, that is a game win, arbitrary points increase based on effectiveness of move 
		if (comarray[x] == 3) {
			points += 1024;
		}
		if ((humanarray[x] == 2) && (humarray[x] == -1)) {
			points += 64;
		}
		if (comarray[x] == 2) {
			points += 16;
		}
		if (humarray[x] == -1) {
			points += 4;
		}
		if (comarray[x] == 1) {
			points += 1;
		}
	}
	int nxtmove = 0; 
	for (int b = 1; b < 10; b++) { //tests next human move as part of determining the next optimal move, integers 1-9 represent spaces on game board
		nxtmove = b; 
		int count = 0; //count integer for cycling through game board positions 1-9, until reaches move position
		for (int k = 0; k < 5; k += 2) {
			for (int l = 0; l < 5; l += 2) {
				if (++count == nxtmove) { //reaches move position
					if (squares[count - 1] == 0) { //if square is empty
						testHumMove(board, comarray, humarray, points, k, l); //tests human move
					}
					else if (squares[count - 1] > 0) { //if square is already full
						nxtmove = 0;
						k = 6; l = 6; //breaks loop
					}
				}
			}
		}
	}

	if (points > most[0]) { //if points indicate it is the optimal move 
		most[0] = points;
		most[1] = i;
		most[2] = j;
		most[3] = move;
	} //stores optimal move and move location data
	board[i][j] = ' '; //clears board of potential moves
}

void testHumMove(char board[5][5], int comarray[8], int humarray[8], int &points, int k, int l) { //tests the next human move as part of determining the optimal position
	board[k][l] = 'x';
	int comarray2[8]; //clone arrays for winning paths
	int humarray2[8]; //clone arrays for winning paths

	for (int i = 0; i < 8; i++) { //initialized with winning path information
		comarray2[i] = comarray[i];
		humarray2[i] = humarray[i];
	}
	switch (board[k][l]) {
	case 'x': //increments for 8 winning conditions if conditions are met
		switch (k) {
		case 0:	humarray2[0]++; break;
		case 2: humarray2[1]++; break;
		case 4: humarray2[2]++; break;
		}
		switch (l) {
		case 0:	humarray2[3]++; break;
		case 2: humarray2[4]++; break;
		case 4: humarray2[5]++; break;
		}
		if (k == l) {
			humarray2[6]++;
		}
		if (k + l == 4) {
			humarray2[7]++;
		}
		break;
	}
	board[k][l] = ' ';
	for (int x = 0; x < 8; x++) {
		if ((comarray2[x] > 0) && (humarray2[x] > 0)) {
			humarray2[x] = -1; comarray2[x] = -1;
		}
	}
	int hcount = 0;
	int ccount = 0;
	for (int x = 0; x < 8; x++) { //conditions determine if human's next move would be detrimental to computer's move 
		if (humarray2[x] == 2) {
			hcount++;
		}
		if (comarray2[x] == 2) {
			ccount++;
		}
	}
	if ((hcount > 1) && (ccount < 1)) {
		points -= 256; //arbitrary point decrease in line with the scale-4 mechanism used previously
	} 
}
