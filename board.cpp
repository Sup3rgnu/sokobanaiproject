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

const int DEBUG_MOVE = 1;
const int DEBUG_VALIDATEMOVE = 1;

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

void board::moveBack(pair<char,bool> move)
{
	visited_boards.pop_back();
	theboard = visited_boards.back();
	//opposite directions
	switch (move.first) {
	case 'U':
		ppos.first += 1 ;
		break;
	case 'L':
		ppos.second += 1;
	case 'D':
		ppos.first -= 1;
	case 'R':
		ppos.second -= 1;
	}

}

void board::printBoard() {

	for(int i = 0; i < theboard.size(); i++) {
		cout << i+1 << "[";
		for(int j = 0; j < theboard[i].size(); j++) {
			cout << theboard[i][j] << ",";
		}
		cout << "]" << endl;
	}
 cout << "player x=" << ppos.first << ", y=" << ppos.second << endl;
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
			if(theboard[(ppos.first)-3][ppos.second] == '#' && (theboard[(ppos.first)-2][(ppos.second)-1] == '#' || theboard[(ppos.first)-2][(ppos.second)+1] == '#')){
				if(DEBUG_VALIDATEMOVE == 1 && true) { cout << "This move would push the box into a corner! Not OK." << endl; }

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
			if(theboard[(ppos.first)+3][ppos.second] == '#' && (theboard[(ppos.first)+2][(ppos.second)-1] == '#' || theboard[(ppos.first)+2][(ppos.second)+1] == '#')){
				if(DEBUG_VALIDATEMOVE == 1 && true) { cout << "This move would push the box into a corner! Not OK." << endl; }

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
			if(theboard[(ppos.first)][ppos.second-3] == '#' && (theboard[(ppos.first)-1][(ppos.second)-2] == '#' || theboard[(ppos.first)+1][(ppos.second)-2] == '#')){
				if(DEBUG_VALIDATEMOVE == 1 && true) { cout << "This move would push the box into a corner! Not OK." << endl; }

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
			if(theboard[ppos.first][ppos.second+3] == '#' && (theboard[(ppos.first)-1][ppos.second+2] == '#' || theboard[ppos.first+1][ppos.second+2] == '#')){
				if(DEBUG_VALIDATEMOVE == 1 && true) { cout << "This move would push the box into a corner! Not OK." << endl; }

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

	if(DEBUG_MOVE == 1 && false) { cout << "move() input: " << c << endl; }

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
			if(DEBUG_MOVE == 1 && true) { cout << "U: Box was hit by player!" << endl; }

			boxaffected = true;

			// Kolla om spelaren skjuter in en l�da i goalsquare-omr�det
			if(theboard[(ppos.first)-2][ppos.second] == '.'  && theboard[(ppos.first)-1][ppos.second] == '$'
				&& theboard[ppos.first][ppos.second] == '@') {
				if(DEBUG_MOVE == 1 && true) { cout << "U: Player moves a box into goal square area." << endl; }
				theboard[(ppos.first)-2][ppos.second] = '*';
				theboard[(ppos.first)-1][ppos.second] = '@';
				theboard[ppos.first][ppos.second] = ' ';
			}
			// Kolla om spelaren skjuter in en l�da i goalsquare-omr�det och �ker med in.
			if(theboard[(ppos.first)-2][ppos.second] == '.'  && theboard[(ppos.first)-1][ppos.second] == '*'
					&& theboard[ppos.first][ppos.second] == '@') {
				if(DEBUG_MOVE == 1 && true) { cout << "U: Player moves a box into goal square area and enters goal square." << endl; }
				theboard[(ppos.first)-2][ppos.second] = '*';
				theboard[(ppos.first)-1][ppos.second] = '+';
				theboard[ppos.first][ppos.second] = ' ';
			}
			// Kolla om spelaren skjuter en l�da inom goalsquare-omr�det
			if(theboard[(ppos.first)-2][ppos.second] == '.'  && theboard[(ppos.first)-1][ppos.second] == '*'
					&& theboard[ppos.first][ppos.second] == '+') {
				if(DEBUG_MOVE == 1 && true) { cout << "U: Player moves a box within goal square area." << endl; }
				theboard[(ppos.first)-2][ppos.second] = '*';
				theboard[(ppos.first)-1][ppos.second] = '+';
				theboard[ppos.first][ppos.second] = '.';
			}
			// Kolla om spelaren skjuter en l�da inom goalsquare-omr�det
			if(theboard[(ppos.first)-2][ppos.second] == ' '  && theboard[(ppos.first)-1][ppos.second] == '*'
					&& theboard[ppos.first][ppos.second] == '+') {
				if(DEBUG_MOVE == 1 && true) { cout << "U: Player moves a box within goal square area." << endl; }
				theboard[(ppos.first)-2][ppos.second] = '$';
				theboard[(ppos.first)-1][ppos.second] = '+';
				theboard[ppos.first][ppos.second] = '.';
			}
			// Kolla om spelaren skjuter en l�da som ligger vid kanten till goalsquare-omr�det
			if(theboard[(ppos.first)-2][ppos.second] == ' '  && theboard[(ppos.first)-1][ppos.second] == '$'
					&& theboard[ppos.first][ppos.second] == '+') {
				if(DEBUG_MOVE == 1 && true) { cout << "U: Player moves a box at the border of goal square area." << endl; }
				theboard[(ppos.first)-2][ppos.second] = '$';
				theboard[(ppos.first)-1][ppos.second] = '@';
				theboard[ppos.first][ppos.second] = '.';
			}
			// Kolla om vi skjuter runt l�dan p� det vanliga golvet.
			if(theboard[(ppos.first)-1][ppos.second] == '$' || theboard[ppos.first][ppos.second] == '@') {
				if(DEBUG_MOVE == 1 && true) { cout << "U: Player moves a box outside of goal squares." << endl; }
				theboard[(ppos.first-2)][ppos.second] = '$';
				theboard[(ppos.first-1)][ppos.second] = '@';
				theboard[ppos.first][ppos.second] = ' ';
			}
		}

		// Kolla om spelarmark�ren g�r in i goalsquare och ska byta mark�r till +.
		else if(theboard[(ppos.first)-1][ppos.second] == '.'  && theboard[ppos.first][ppos.second] == '@' && !boxaffected) {
			if(DEBUG_MOVE == 1 && true) { cout << "U: Player enters a goal square." << endl; }
			theboard[(ppos.first)-1][ppos.second] = '+';
			theboard[ppos.first][ppos.second] = ' ';
		}
		// Kolla om spelarmark�ren redan var i goal square och l�gg tillbaka en . bakom spelaren.
		else if(theboard[(ppos.first)-1][ppos.second] == '.'  && theboard[ppos.first][ppos.second] == '+' && !boxaffected) {
			if(DEBUG_MOVE == 1 && true) { cout << "U: Player moves from one goal square to another." << endl; }
			theboard[(ppos.first)-1][ppos.second] = '+';
			theboard[ppos.first][ppos.second] = '.';
		}
		// Kolla om spelarmark�ren l�mnar goal square omr�det. Tillbaka till @ allts�.
		else if(theboard[(ppos.first)-1][ppos.second] == ' '  && theboard[ppos.first][ppos.second] == '+' && !boxaffected) {
			if(DEBUG_MOVE == 1 && true) { cout << "U: Player moves from one goal square to regular area." << endl; }
			theboard[(ppos.first)-1][ppos.second] = '@';
			theboard[ppos.first][ppos.second] = '.';
		}
		else { // Om vi inte p�verkar l�dan.
			if(DEBUG_MOVE == 1 && true) { cout << "U: Player just moves in the regular floor area." << endl; }
			theboard[((ppos.first)-1)][ppos.second] = '@';
			theboard[ppos.first][ppos.second] = ' ';
		}
		ppos = make_pair((ppos.first-1), ppos.second); // Nya spelarpositionen p� br�dan.
	}

	/* D D D D D D D D D D D D D D D D D D D D D */

	if(c == 'D') {
		if(DEBUG_MOVE == 1 && true) { cout << "Input was: D" << endl; }
		// Kolla om vi p�verkar en l�da.
		if(theboard[(ppos.first)+1][ppos.second] == '$' || theboard[(ppos.first)+1][ppos.second] == '*') {
			if(DEBUG_MOVE == 1 && true) { cout << "D: Box was hit by player!" << endl; }

			boxaffected = true;

			// Kolla om spelaren skjuter in en l�da i goalsquare-omr�det
			if(theboard[(ppos.first)+2][ppos.second] == '.'  && theboard[(ppos.first)+1][ppos.second] == '$'
				&& theboard[ppos.first][ppos.second] == '@') {
				if(DEBUG_MOVE == 1 && true) { cout << "D: Player moves a box into goal square area." << endl; }
				theboard[(ppos.first)+2][ppos.second] = '*';
				theboard[(ppos.first)+1][ppos.second] = '@';
				theboard[ppos.first][ppos.second] = ' ';
			}
			// Kolla om spelaren skjuter in en l�da i goalsquare-omr�det och �ker med in.
			if(theboard[(ppos.first)+2][ppos.second] == '.'  && theboard[(ppos.first)+1][ppos.second] == '*'
					&& theboard[ppos.first][ppos.second] == '@') {
				if(DEBUG_MOVE == 1 && true) { cout << "D: Player moves a box into goal square area and enters goal square." << endl; }
				theboard[(ppos.first)+2][ppos.second] = '*';
				theboard[(ppos.first)+1][ppos.second] = '+';
				theboard[ppos.first][ppos.second] = ' ';
			}
			// Kolla om spelaren skjuter en l�da inom goalsquare-omr�det
			if(theboard[(ppos.first)+2][ppos.second] == '.'  && theboard[(ppos.first)+1][ppos.second] == '*'
					&& theboard[ppos.first][ppos.second] == '+') {
				if(DEBUG_MOVE == 1 && true) { cout << "D: Player moves a box within goal square area." << endl; }
				theboard[(ppos.first)+2][ppos.second] = '*';
				theboard[(ppos.first)+1][ppos.second] = '+';
				theboard[ppos.first][ppos.second] = '.';
			}
			// Kolla om spelaren skjuter en l�da ut fr�n goalsquare-omr�det
			if(theboard[(ppos.first)+2][ppos.second] == ' '  && theboard[(ppos.first)+1][ppos.second] == '*'
					&& theboard[ppos.first][ppos.second] == '+') {
				if(DEBUG_MOVE == 1 && true) { cout << "D: Player moves a box within goal square area." << endl; }
				theboard[(ppos.first)+2][ppos.second] = '$';
				theboard[(ppos.first)+1][ppos.second] = '+';
				theboard[ppos.first][ppos.second] = '.';
			}
			// Kolla om spelaren skjuter en l�da som ligger vid kanten till goalsquare-omr�det
			if(theboard[(ppos.first)+2][ppos.second] == ' '  && theboard[(ppos.first)+1][ppos.second] == '$'
					&& theboard[ppos.first][ppos.second] == '+') {
				if(DEBUG_MOVE == 1 && true) { cout << "D: Player moves a box at the border of goal square area." << endl; }
				theboard[(ppos.first)+2][ppos.second] = '$';
				theboard[(ppos.first)+1][ppos.second] = '@';
				theboard[ppos.first][ppos.second] = '.';
			}
			// Kolla om vi skjuter runt l�dan p� det vanliga golvet.
			if(theboard[(ppos.first)+1][ppos.second] == '$' || theboard[ppos.first][ppos.second] == '@') {
				if(DEBUG_MOVE == 1 && true) { cout << "D: Player moves a box outside of goal squares." << endl; }
				theboard[(ppos.first+2)][ppos.second] = '$';
				theboard[(ppos.first+1)][ppos.second] = '@';
				theboard[ppos.first][ppos.second] = ' ';
			}
		}

		// Kolla om spelarmark�ren g�r in i goalsquare och ska byta mark�r till +.
		else if(theboard[(ppos.first)+1][ppos.second] == '.'  && theboard[ppos.first][ppos.second] == '@' && !boxaffected) {
			if(DEBUG_MOVE == 1 && true) { cout << "D: Player enters a goal square." << endl; }
			theboard[(ppos.first)+1][ppos.second] = '+';
			theboard[ppos.first][ppos.second] = ' ';
		}
		// Kolla om spelarmark�ren redan var i goal square och l�gg tillbaka en . bakom spelaren.
		else if(theboard[(ppos.first)+1][ppos.second] == '.'  && theboard[ppos.first][ppos.second] == '+' && !boxaffected) {
			if(DEBUG_MOVE == 1 && true) { cout << "D: Player moves from one goal square to another." << endl; }
			theboard[(ppos.first)+1][ppos.second] = '+';
			theboard[ppos.first][ppos.second] = '.';
		}
		// Kolla om spelarmark�ren l�mnar goal square omr�det. Tillbaka till @ allts�.
		else if(theboard[(ppos.first)+1][ppos.second] == ' '  && theboard[ppos.first][ppos.second] == '+' && !boxaffected) {
			if(DEBUG_MOVE == 1 && true) { cout << "D: Player moves from one goal square to regular area." << endl; }
			theboard[(ppos.first)+1][ppos.second] = '@';
			theboard[ppos.first][ppos.second] = '.';
		}
		else { // Om vi inte p�verkar l�dan.
			if(DEBUG_MOVE == 1 && true) { cout << "D: Player just moves in the regular floor area." << endl; }
			theboard[((ppos.first)+1)][ppos.second] = '@';
			theboard[ppos.first][ppos.second] = ' ';
		}
		ppos = make_pair((ppos.first+1), ppos.second); // Nya spelarpositionen p� br�dan.
	}

	/* L L L L L L L L L L L L L L L L L L L L */

	if(c == 'L') {
		if(DEBUG_MOVE == 1 && true) { cout << "Input was: L" << endl; }
		// Kolla om vi p�verkar en l�da.
		if(theboard[ppos.first][ppos.second-1] == '$' || theboard[ppos.first][ppos.second-1] == '*') {
			if(DEBUG_MOVE == 1 && true) { cout << "L: Box was hit by player!" << endl; }

			boxaffected = true;

			// Kolla om spelaren skjuter in en l�da i goalsquare-omr�det
			if(theboard[ppos.first][ppos.second-2] == '.'  && theboard[ppos.first][ppos.second-1] == '$'
					&& theboard[ppos.first][ppos.second] == '@') {
				if(DEBUG_MOVE == 1 && true) { cout << "L: Player moves a box into goal square area." << endl; }
				theboard[ppos.first][ppos.second-2] = '*';
				theboard[ppos.first][ppos.second-1] = '@';
				theboard[ppos.first][ppos.second] = ' ';
			}
			// Kolla om spelaren skjuter in en l�da i goalsquare-omr�det och �ker med in.
			if(theboard[ppos.first][ppos.second-2] == '.'  && theboard[ppos.first][ppos.second-1] == '*'
					&& theboard[ppos.first][ppos.second] == '@') {
				if(DEBUG_MOVE == 1 && true) { cout << "L: Player moves a box into goal square area and enters goal square." << endl; }
				theboard[ppos.first][ppos.second-2] = '*';
				theboard[ppos.first][ppos.second-1] = '+';
				theboard[ppos.first][ppos.second] = ' ';
			}
			// Kolla om spelaren skjuter en l�da inom goalsquare-omr�det
			if(theboard[ppos.first][ppos.second-2] == '.'  && theboard[ppos.first][ppos.second-1] == '*'
					&& theboard[ppos.first][ppos.second] == '+') {
				if(DEBUG_MOVE == 1 && true) { cout << "L: Player moves a box within goal square area." << endl; }
				theboard[ppos.first][ppos.second-2] = '*';
				theboard[ppos.first][ppos.second-1] = '+';
				theboard[ppos.first][ppos.second] = '.';
			}
			// Kolla om spelaren skjuter en l�da ut fr�n goalsquare-omr�det
			if(theboard[ppos.first][ppos.second-2] == ' '  && theboard[ppos.first][ppos.second-1] == '*'
					&& theboard[ppos.first][ppos.second] == '+') {
				if(DEBUG_MOVE == 1 && true) { cout << "L: Player moves a box within goal square area." << endl; }
				theboard[ppos.first][ppos.second-2] = '$';
				theboard[ppos.first][ppos.second-1] = '+';
				theboard[ppos.first][ppos.second] = '.';
			}
			// Kolla om spelaren skjuter en l�da som ligger vid kanten till goalsquare-omr�det
			if(theboard[ppos.first][ppos.second-2] == ' '  && theboard[ppos.first][ppos.second-1] == '$'
					&& theboard[ppos.first][ppos.second] == '+') {
				if(DEBUG_MOVE == 1 && true) { cout << "L: Player moves a box at the border of goal square area." << endl; }
				theboard[ppos.first][ppos.second-2] = '$';
				theboard[ppos.first][ppos.second-1] = '@';
				theboard[ppos.first][ppos.second] = '.';
			}
			// Kolla om vi skjuter runt l�dan p� det vanliga golvet.
			if(theboard[ppos.first][ppos.second-1] == '$' || theboard[ppos.first][ppos.second] == '@') {
				if(DEBUG_MOVE == 1 && true) { cout << "L: Player moves a box outside of goal squares." << endl; }
				theboard[(ppos.first)][ppos.second-2] = '$';
				theboard[(ppos.first)][ppos.second-1] = '@';
				theboard[ppos.first][ppos.second] = ' ';
			}
		}

		// Kolla om spelarmark�ren g�r in i goalsquare och ska byta mark�r till +.
		else if(theboard[ppos.first][ppos.second-1] == '.'  && theboard[ppos.first][ppos.second] == '@' && !boxaffected) {
			if(DEBUG_MOVE == 1 && true) { cout << "L: Player enters a goal square." << endl; }
			theboard[ppos.first][ppos.second-1] = '+';
			theboard[ppos.first][ppos.second] = ' ';
		}
		// Kolla om spelarmark�ren redan var i goal square och l�gg tillbaka en . bakom spelaren.
		else if(theboard[ppos.first][ppos.second-1] == '.'  && theboard[ppos.first][ppos.second] == '+' && !boxaffected) {
			if(DEBUG_MOVE == 1 && true) { cout << "L: Player moves from one goal square to another." << endl; }
			theboard[ppos.first][ppos.second-1] = '+';
			theboard[ppos.first][ppos.second] = '.';
		}
		// Kolla om spelarmark�ren l�mnar goal square omr�det. Tillbaka till @ allts�.
		else if(theboard[ppos.first][ppos.second-1] == ' '  && theboard[ppos.first][ppos.second] == '+' && !boxaffected) {
			if(DEBUG_MOVE == 1 && true) { cout << "L: Player moves from one goal square to regular area." << endl; }
			theboard[ppos.first][ppos.second-1] = '@';
			theboard[ppos.first][ppos.second] = '.';
		}
		else { // Om vi inte p�verkar l�dan.
			if(DEBUG_MOVE == 1 && true) { cout << "L: Player just moves in the regular floor area." << endl; }
			theboard[(ppos.first)][ppos.second-1] = '@';
			theboard[ppos.first][ppos.second] = ' ';
		}
		ppos = make_pair((ppos.first), ppos.second-1); // Nya spelarpositionen p� br�dan.
	}

	/* R R R R R R R R R R R R R R R R R R R R */

	if(c == 'R') {
		if(DEBUG_MOVE == 1 && true) { cout << "Input was: R" << endl; }
		// Kolla om vi p�verkar en l�da.
		if(theboard[ppos.first][ppos.second+1] == '$' || theboard[ppos.first][ppos.second+1] == '*') {
			if(DEBUG_MOVE == 1 && true) { cout << "R: Box was hit by player!" << endl; }

			boxaffected = true;

			// Kolla om spelaren skjuter in en l�da i goalsquare-omr�det
			if(theboard[ppos.first][ppos.second+2] == '.'  && theboard[ppos.first][ppos.second+1] == '$'
					&& theboard[ppos.first][ppos.second] == '@') {
				if(DEBUG_MOVE == 1 && true) { cout << "R: Player moves a box into goal square area." << endl; }
				theboard[ppos.first][ppos.second+2] = '*';
				theboard[ppos.first][ppos.second+1] = '@';
				theboard[ppos.first][ppos.second] = ' ';
			}
			// Kolla om spelaren skjuter in en l�da i goalsquare-omr�det och �ker med in.
			if(theboard[ppos.first][ppos.second+2] == '.'  && theboard[ppos.first][ppos.second+1] == '*'
					&& theboard[ppos.first][ppos.second] == '@') {
				if(DEBUG_MOVE == 1 && true) { cout << "R: Player moves a box into goal square area and enters goal square." << endl; }
				theboard[ppos.first][ppos.second+2] = '*';
				theboard[ppos.first][ppos.second+1] = '+';
				theboard[ppos.first][ppos.second] = ' ';
			}
			// Kolla om spelaren skjuter en l�da inom goalsquare-omr�det
			if(theboard[ppos.first][ppos.second+2] == '.'  && theboard[ppos.first][ppos.second+1] == '*'
					&& theboard[ppos.first][ppos.second] == '+') {
				if(DEBUG_MOVE == 1 && true) { cout << "R: Player moves a box within goal square area." << endl; }
				theboard[ppos.first][ppos.second+2] = '*';
				theboard[ppos.first][ppos.second+1] = '+';
				theboard[ppos.first][ppos.second] = '.';
			}
			// Kolla om spelaren skjuter en l�da ut fr�n goalsquare-omr�det
			if(theboard[ppos.first][ppos.second+2] == ' '  && theboard[ppos.first][ppos.second+1] == '*'
					&& theboard[ppos.first][ppos.second] == '+') {
				if(DEBUG_MOVE == 1 && true) { cout << "R: Player moves a box within goal square area." << endl; }
				theboard[ppos.first][ppos.second+2] = '$';
				theboard[ppos.first][ppos.second+1] = '+';
				theboard[ppos.first][ppos.second] = '.';
			}
			// Kolla om spelaren skjuter en l�da som ligger vid kanten till goalsquare-omr�det
			if(theboard[ppos.first][ppos.second+2] == ' '  && theboard[ppos.first][ppos.second+1] == '$'
					&& theboard[ppos.first][ppos.second] == '+') {
				if(DEBUG_MOVE == 1 && true) { cout << "R: Player moves a box at the border of goal square area." << endl; }
				theboard[ppos.first][ppos.second+2] = '$';
				theboard[ppos.first][ppos.second+1] = '@';
				theboard[ppos.first][ppos.second] = '.';
			}
			// Kolla om vi skjuter runt l�dan p� det vanliga golvet.
			if(theboard[ppos.first][ppos.second+1] == '$' || theboard[ppos.first][ppos.second] == '@') {
				if(DEBUG_MOVE == 1 && true) { cout << "R: Player moves a box outside of goal squares." << endl; }
				theboard[(ppos.first)][ppos.second+2] = '$';
				theboard[(ppos.first)][ppos.second+1] = '@';
				theboard[ppos.first][ppos.second] = ' ';
			}
		}

		// Kolla om spelarmark�ren g�r in i goalsquare och ska byta mark�r till +.
		else if(theboard[ppos.first][ppos.second+1] == '.'  && theboard[ppos.first][ppos.second] == '@' && !boxaffected) {
			if(DEBUG_MOVE == 1 && true) { cout << "R: Player enters a goal square." << endl; }
			theboard[ppos.first][ppos.second+1] = '+';
			theboard[ppos.first][ppos.second] = ' ';
		}
		// Kolla om spelarmark�ren redan var i goal square och l�gg tillbaka en . bakom spelaren.
		else if(theboard[ppos.first][ppos.second+1] == '.'  && theboard[ppos.first][ppos.second] == '+' && !boxaffected) {
			if(DEBUG_MOVE == 1 && true) { cout << "R: Player moves from one goal square to another." << endl; }
			theboard[ppos.first][ppos.second+1] = '+';
			theboard[ppos.first][ppos.second] = '.';
		}
		// Kolla om spelarmark�ren l�mnar goal square omr�det. Tillbaka till @ allts�.
		else if(theboard[ppos.first][ppos.second+1] == ' '  && theboard[ppos.first][ppos.second] == '+' && !boxaffected) {
			if(DEBUG_MOVE == 1 && true) { cout << "R: Player moves from one goal square to regular area." << endl; }
			theboard[ppos.first][ppos.second+1] = '@';
			theboard[ppos.first][ppos.second] = '.';
		}
		else { // Om vi inte p�verkar l�dan.
			if(DEBUG_MOVE == 1 && true) { cout << "R: Player just moves in the regular floor area." << endl; }
			theboard[(ppos.first)][ppos.second+1] = '@';
			theboard[ppos.first][ppos.second] = ' ';
		}
		ppos = make_pair((ppos.first), ppos.second+1); // Nya spelarpositionen p� br�dan.
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
	int i=0;
	string m;

	while(1) {
		for(i; moves[i];) {
			if(validateMove(moves[i])) {
				solution.push_back(move(moves[i]));
				if(currentBoardVisited()) {
					//add the board just so we can remove a board in the backtracking step
					visited_boards.push_back(theboard);
					cout << "wrong move '" << moves[i] << "' made, board already visited, backtracking---------------------\n";
					break; //backtrack
				}
				visited_boards.push_back(theboard);
				i = 0;
				getline(cin, m, '\n');
			} else {
				i++;
			}

		}
		//backtracking
		while(1) {
			pair<char, bool> last_move = solution.back();
			solution.pop_back();
			moveBack(last_move);
			cout << "after backtracking including moveBack the board looks like:\n";
			printBoard();
			int j;
			for(j = 0; last_move.first != moves[j]; j++)
				;
			if(moves[j+1]) {
				i = j + 1;
				break;
			}
		}
	}
}

bool board::currentBoardVisited() {
	int i;
	for(i = 0; i < visited_boards.size(); i++) {
	 if(theboard == visited_boards[i])
		 return 1;
	}
	return 0;
}


