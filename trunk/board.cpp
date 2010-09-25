/*
 * File:   board.h
 * Author: Voddlerdoods
 *
 * Created on September 21, 2010, 3:00 PM
 */

#include "board.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <utility>
#include <assert.h>

const int DEBUG_MOVE = 0;
const int DEBUG_VALIDATEMOVE = 0;

using namespace std;

board::board (string board1){

	stringstream ss(board1);
	string token;

	/* Dessa beh�vs f�r att h�lla reda p� var i vectormatrisen vi �r n�r vi st�ter p�
	 * spelare s� den kan sparas i ppos
	 */
	int row = 0;
	int col = 0;
	vector<char> newrow;

	/* L�ser indata via en stringstream och splittar p� rad
	 * och sedan per char som stoppas i en 2d vector.
	 */
	while(getline(ss, token, '\n')) {

		const char *strp = token.c_str();

		while(*strp != '\0') {
			newrow.push_back(*strp++);
			col++;
			if(*strp == '@') {
				ppos = make_pair(row, col);
			}
		}

		theboard.push_back(newrow);

		newrow.clear();
		token.clear();
		row++;
		col = 0;
	}
	printBoard();
}

void board::printBoard() {

	for(int i = 0; i < theboard.size(); i++) {
		cout << i+1 << "[";
		for(int j = 0; j < theboard[i].size(); j++) {
			cout << theboard[i][j] << ",";
		}
		cout << "]" << endl;
	}

}

bool board::goalTest() {
	for(int i = 0; i < theboard.size(); i++)
			for(int j = 0; j < theboard[i].size(); j++)
				if (theboard[i][j] == '$')
					return false;
		return true;
}

bool board::validateMove(char c) {

	if(DEBUG_VALIDATEMOVE == 1 && true) { cout << "validateMove() input: " << c << endl; }

	bool ok = true;

	if(DEBUG_VALIDATEMOVE == 1 && true) { cout << "Status at start: " << ok << endl; }

	assert(c == 'U' || c == 'D' || c == 'L' || c == 'R');

	if(c == 'U') {
		// Kolla om vi tr�ffar en box.
		if(theboard[(ppos.first)-1][ppos.second] == '$' || theboard[(ppos.first)-1][ppos.second] == '*') {
			if(DEBUG_VALIDATEMOVE == 1 && true) { cout << "Box will be affected." << endl; }

			if(theboard[(ppos.first)-2][ppos.second] == '#' || theboard[(ppos.first)-2][ppos.second] == '$'){
				if(DEBUG_VALIDATEMOVE == 1 && true) { cout << "This move would push the box into something! Not OK." << endl; }

				ok = false;
			}
		}
		if(DEBUG_VALIDATEMOVE == 1 && true) { cout << "There is no box in the way." << endl; }

		if(theboard[(ppos.first)-1][ppos.second] == '#'){
			if(DEBUG_VALIDATEMOVE == 1 && true) { cout << "You are trying to go into a wall. Not OK." << endl; }

			ok = false;
		}

	}

	else if(c == 'D') {
		if(theboard[((ppos.first)+1)][ppos.second] == '$' || theboard[(ppos.first)+1][ppos.second] == '*') {
			if(DEBUG_VALIDATEMOVE == 1 && true) { cout << "Box will be affected." << endl; }

			if(theboard[(ppos.first)+2][ppos.second] == '#' || theboard[(ppos.first)+2][ppos.second] == '$'){
				if(DEBUG_VALIDATEMOVE == 1 && true) { cout << "This move would push the box into something! Not OK." << endl; }

					ok = false;
				}
			}
			if(DEBUG_VALIDATEMOVE == 1 && true) { cout << "There is no box in the way." << endl; }

			if(theboard[(ppos.first)+1][ppos.second] == '#'){
				if(DEBUG_VALIDATEMOVE == 1 && true) { cout << "You are trying to go into a wall. Not OK." << endl; }

				ok = false;
			}
	}

	else if(c == 'L') {
		if(theboard[ppos.first][(ppos.second)-1] == '$' || theboard[ppos.first][(ppos.second)-1] == '*') {
			if(DEBUG_VALIDATEMOVE == 1 && true) { cout << "Box will be affected." << endl; }

			if(theboard[ppos.first][(ppos.second)-2] == '#' || theboard[ppos.first][(ppos.second)-2] == '$'){
				if(DEBUG_VALIDATEMOVE == 1 && true) { cout << "This move would push the box into something! Not OK." << endl; }

					ok = false;
				}
			}
			if(DEBUG_VALIDATEMOVE == 1 && true) { cout << "There is no box in the way." << endl; }

			if(theboard[ppos.first][(ppos.second)-1] == '#'){
				if(DEBUG_VALIDATEMOVE == 1 && true) { cout << "You are trying to go into a wall. Not OK." << endl; }

				ok = false;
			}
	}

	else if(c == 'R') {
		if(theboard[ppos.first][(ppos.second)+1] == '$' || theboard[ppos.first][(ppos.second)+1] == '*') {
			if(DEBUG_VALIDATEMOVE == 1 && true) { cout << "Box will be affected." << endl; }

			if(theboard[ppos.first][(ppos.second)+2] == '#' || theboard[ppos.first][(ppos.second)+2] == '$'){
				if(DEBUG_VALIDATEMOVE == 1 && true) { cout << "This move would push the box into something! Not OK." << endl; }

				ok = false;
			}
		}
		if(DEBUG_VALIDATEMOVE == 1 && true) { cout << "There is no box in the way." << endl; }

		if(theboard[ppos.first][(ppos.second)+1] == '#'){
			if(DEBUG_VALIDATEMOVE == 1 && true) { cout << "You are trying to go into a wall. Not OK." << endl; }

			ok = false;
		}
	}

	if(DEBUG_VALIDATEMOVE == 1 && true) { cout << "Status at end: " << ok << endl; }

	return ok;
}

/* validateMove skall alltid anropas fore move().
 *
 * if(b.validateMove(m) {
 * 	b.move(m)
 * }
 */
pair<char, bool> board::move(char c) {

	if(DEBUG_MOVE == 1 && true) { cout << "move() input: " << c << endl; }

	/* bra grejer att veta
	 * board[rows][cols]
	 * Wall 	 # 	 0x23
	 * Player 	@ 	0x40
	 * Player on goal square 	+ 	0x2b
	 * Box 	$ 	0x24
	 * Box on goal square 	* 	0x2a
	 * Goal square 	. 	0x2e
	 * Floor 	(Space) 	0x20 */

	bool boxaffected = false;

	assert(c == 'U' || c == 'D' || c == 'L' || c == 'R');

	if(c == 'U') {
		if(DEBUG_MOVE == 1 && true) { cout << "Input was: U" << endl; }
		// Kolla om vi p�verkar en l�da.
		if(theboard[(ppos.first)-1][ppos.second] == '$' || theboard[(ppos.first)-1][ppos.second] == '*') {
			if(DEBUG_MOVE == 1 && true) { cout << "Box was hit by player!" << endl; }

			theboard[(ppos.first-2)][ppos.second] = '$';
			theboard[(ppos.first-1)][ppos.second] = '@';
			theboard[ppos.first][ppos.second] = ' ';
			boxaffected = true;
		}
		else { // Om vi inte p�verkar l�dan.
			theboard[((ppos.first)-1)][ppos.second] = '@';
			theboard[ppos.first][ppos.second] = ' ';
		}
		ppos = make_pair((ppos.first-1), ppos.second); // Nya spelarpositionen p� br�dan.
	}

	else if(c == 'D') {
	if(DEBUG_MOVE == 1 && true) { cout << "Input was: D" << endl; }
		// Kolla om vi p�verkar en l�da.
		if(theboard[((ppos.first)+1)][ppos.second] == '$' || theboard[(ppos.first)+1][ppos.second] == '*') {
			if(DEBUG_MOVE == 1 && true) { cout << "Box was hit by player!" << endl; }

			theboard[((ppos.first)+2)][ppos.second] = '$';
			theboard[((ppos.first)+1)][ppos.second] = '@';
			theboard[(ppos.first)][ppos.second] = ' ';
			boxaffected = true;
		}
		else { // Om vi inte p�verkar l�dan.
					theboard[(ppos.first+1)][ppos.second] = '@';
					theboard[ppos.first][ppos.second] = ' ';
		}
		ppos = make_pair((ppos.first+1), ppos.second); // Nya spelarpositionen p� br�dan.
	}

	else if(c == 'L') {
	if(DEBUG_MOVE == 1 && true) { cout << "Input was: L" << endl; }
		// Kolla om vi p�verkar en l�da.
		if(theboard[ppos.first][(ppos.second)-1] == '$' || theboard[ppos.first][(ppos.second)-1] == '*') {
			if(DEBUG_MOVE == 1 && true) { cout << "Box was hit by player!" << endl; }

			theboard[ppos.first][(ppos.second)-2] = '$';
			theboard[ppos.first][(ppos.second)-1] = '@';
			theboard[(ppos.first)][ppos.second] = ' ';
			boxaffected = true;
		}
		else { // Om vi inte p�verkar l�dan.
					theboard[ppos.first][(ppos.second-1)] = '@';
					theboard[ppos.first][ppos.second] = ' ';
		}
		ppos = make_pair(ppos.first, (ppos.second-1)); // Nya spelarpositionen p� br�dan.
	}

	else if(c == 'R') {
		if(DEBUG_MOVE == 1 && true) { cout << "Input was: R" << endl; }
			// Kolla om vi p�verkar en l�da.
			if(theboard[ppos.first][(ppos.second)+1] == '$' || theboard[ppos.first][(ppos.second)+1] == '*') {
				if(DEBUG_MOVE == 1 && true) { cout << "Box was hit by player!" << endl; }

				theboard[ppos.first][(ppos.second)+2] = '$';
				theboard[ppos.first][(ppos.second)+1] = '@';
				theboard[(ppos.first)][ppos.second] = ' ';
				boxaffected = true;
			}
			else { // Om vi inte p�verkar l�dan.
						theboard[ppos.first][(ppos.second+1)] = '@';
						theboard[ppos.first][ppos.second] = ' ';
			}
			ppos = make_pair(ppos.first, (ppos.second+1)); // Nya spelarpositionen p� br�dan.
		}

	if(DEBUG_MOVE == 1 && true) { cout << "move() result:" << endl; printBoard(); }

	return make_pair(c, boxaffected);
}

void board::updateBoard(pair<char, bool> m) {
	switch(m.first) {
	case 'U':
		break;
	case 'D':
		break;
	case 'L':
		break;
	case 'R':
		break;

	}
}

void board::solve() {

	char moves[]= {'U','L','D', 'R', 0};
	int i;

	while(1) {
	 for(i = 0; moves[i]; i++) {
		if(validateMove(moves[i])) {
			solution.push_back(move(moves[i]));
			break;
		}
	 }
	}
}


