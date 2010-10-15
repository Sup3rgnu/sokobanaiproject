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

#define DEBUG_ALL 0
#define USE_WALL  0
#define USE_REACH 1
#define USE_HASH  1
using namespace std;

#if DEBUG_ALL
#define DEBUG(x) x
#else
#define DEBUG(x)
#endif

long board::getHash(vector< vector<char> > board1) {
	locale loc;                 // the "C" locale
	string board_string;
	int i, j;
	const collate<char>& coll = use_facet<collate<char> >(loc);

	for(i = 0; i < board1.size(); i++) {
		for(j = 0; j < board1[i].size(); j++) {
			board_string += board1[i][j];
		}
	}
	return coll.hash(board_string.data(),board_string.data()+board_string.length());
}


board::board (string board1){

	stringstream ss(board1);
	string token;
	nodes_checked = 0;
	nodes_checked_last_time = 0;

	/* Dessa beh�vs f�r att h�lla reda p� var i vectormatrisen vi �r n�r vi st�ter p�
	 * spelare s� den kan sparas i ppos
	 */
	int row = 0;
	int col = 0;
	vector<char> newrow;

	gettimeofday(&time_begin, 0);
	second_checked = 0;

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
#if USE_HASH
	visited_hashed_boards.pop_back();
#endif
	theboard = visited_boards.back();
	//opposite directions
	switch (move.first) {
	case 'U':
		ppos.first += 1 ;
		break;
	case 'L':
		ppos.second += 1;
		break;
	case 'D':
		ppos.first -= 1;
		break;
	case 'R':
		ppos.second -= 1;
		break;
	}

}

void board::printBoard() {

	for(int i = 0; i < theboard.size(); i++) {
		DEBUG(cout << i << "[");
		for(int j = 0; j < theboard[i].size(); j++) {
			DEBUG(cout << theboard[i][j] << ",");
		}
		DEBUG(cout << "]" << endl);
	}
	DEBUG(cout << "player x=" << ppos.second << " ,y=" << ppos.first <<
			", depth=" << solution.size() << ", nodes_checked = " << nodes_checked <<
			", visited_boards.size() = " << visited_boards.size() << endl);
	DEBUG(cout << "solution = " << generate_answer_string() << endl);

}

bool board::goalTest() {
	for(int i = 0; i < theboard.size(); i++)
		for(int j = 0; j < theboard[i].size(); j++)
			if (theboard[i][j] == '$')
				return false;
	return true;
}

bool board::wallCheck(char m) {
#if USE_WALL == 0
	return 0;
#endif
	switch (m) {
	case 'U':
		//check if wall ahead
		if(ppos.first-3 >= 0 && theboard[(ppos.first)-3][ppos.second] == '#' && theboard[(ppos.first)-2][ppos.second] == ' '){
			//find corners
			int xl, xr;
			for(xl = ppos.second; theboard[ppos.first-2][xl] != '#'; xl--)
				;
			for(xr = ppos.second; theboard[ppos.first-2][xr] != '#'; xr++)
				;
			//check if wall between corners
			for(int i = xl+1; i < xr; i++) {
				if(!(theboard[ppos.first-3][i] == '#' && theboard[ppos.first-2][i] == ' '))
					return false;
			}
			return true;
		} else {
			return false;
		}
	case 'D':
		//check if wall ahead
		if(ppos.first+3 <= theboard.size() && theboard[(ppos.first)+3][ppos.second] == '#' && theboard[(ppos.first)+2][ppos.second] == ' '){
			//find corners
			int xl, xr;
			for(xl = ppos.second; theboard[ppos.first+2][xl] != '#'; xl--)
				;
			for(xr = ppos.second; theboard[ppos.first+2][xr] != '#'; xr++)
				;
			//check if wall between corners
			for(int i = xl+1; i < xr; i++) {
				if(!(theboard[ppos.first+3][i] == '#' && theboard[ppos.first+2][i] == ' '))
					return false;
			}
			return true;
		} else {
			return false;
		}
	case 'L':
		//check if wall ahead
		if(ppos.second-3 >= 0 && theboard[ppos.first][ppos.second-3] == '#' && theboard[ppos.first][ppos.second-2] == ' '){
			//find corners
			int yl, yh;
			for(yl = ppos.first; theboard[yl][ppos.first-2] != '#'; yl--)
				;
			for(yh = ppos.first; theboard[yh][ppos.first-2] != '#'; yh++)
				;
			//check if wall between corners
			for(int i = yl+1; i < yh; i++) {
				if(!(theboard[i][ppos.second-3] == '#' && theboard[i][ppos.second-2] == ' '))
					return false;
			}
			return true;
		} else {
			return false;
		}
	case 'R':
		//check if wall ahead
		if(ppos.second+3 <= theboard[ppos.first].size() && theboard[ppos.first][ppos.second+3] == '#' && theboard[ppos.first][ppos.second+2] == ' '){
			//find corners
			int yl, yh;
			for(yl = ppos.first; theboard[yl][ppos.first+2] != '#'; yl--)
				;
			for(yh = ppos.first; theboard[yh][ppos.first+2] != '#'; yh++)
				;
			//check if wall between corners
			for(int i = yl+1; i < yh; i++) {
				if(!(theboard[i][ppos.second+3] == '#' && theboard[i][ppos.second+2] == ' '))
					return false;
			}
			return true;
		} else {
			return false;
		}	default:
		break;
	}
	return false;
}

bool board::validateMove(char c) {

	if(DEBUG_VALIDATEMOVE == 1 && true) { DEBUG(cout << "validateMove() input: " << c << endl); }

	bool ok = true;

	if(DEBUG_VALIDATEMOVE == 1 && true) { DEBUG(cout << "Status at start: " << ok << endl); }

	assert(c == 'U' || c == 'D' || c == 'L' || c == 'R');

	if(c == 'U') {
		// Kolla om vi tr�ffar en box.
		if(theboard[(ppos.first)-1][ppos.second] == '$' || theboard[(ppos.first)-1][ppos.second] == '*') {
			if(DEBUG_VALIDATEMOVE == 1 && true) { DEBUG(cout << "Box will be affected." << endl); }

			if(theboard[(ppos.first)-2][ppos.second] == '#' || theboard[(ppos.first)-2][ppos.second] == '$'){
				if(DEBUG_VALIDATEMOVE == 1 && true) { DEBUG(cout << "This move would push the box into something! Not OK." << endl); }

				ok = false;
			}
			else if(theboard[(ppos.first)-2][ppos.second] == ' ' && theboard[(ppos.first)-3][ppos.second] == '#' && (theboard[(ppos.first)-2][(ppos.second)-1] == '#' || theboard[(ppos.first)-2][(ppos.second)+1] == '#')){
				if(DEBUG_VALIDATEMOVE == 1 && true) { DEBUG(cout << "This move would push the box into a corner! Not OK." << endl); }

				ok = false;
			}
			if(wallCheck(c)){
				DEBUG(cout << "wall!!!" << endl);
				ok = false;
			}
		}
		if(DEBUG_VALIDATEMOVE == 1 && true) { DEBUG(cout << "There is no box in the way." << endl); }

		if(theboard[(ppos.first)-1][ppos.second] == '#'){
			if(DEBUG_VALIDATEMOVE == 1 && true) { DEBUG(cout << "You are trying to go into a wall. Not OK." << endl); }

			ok = false;
		}

	}

	else if(c == 'D') {
		if(theboard[((ppos.first)+1)][ppos.second] == '$' || theboard[(ppos.first)+1][ppos.second] == '*') {
			if(DEBUG_VALIDATEMOVE == 1 && true) { DEBUG(cout << "Box will be affected." << endl); }

			if(theboard[(ppos.first)+2][ppos.second] == '#' || theboard[(ppos.first)+2][ppos.second] == '$'){
				if(DEBUG_VALIDATEMOVE == 1 && true) { DEBUG(cout << "This move would push the box into something! Not OK." << endl); }

				ok = false;
			}
			else if(theboard[(ppos.first)+2][ppos.second] == ' ' && theboard[(ppos.first)+3][ppos.second] == '#' && (theboard[(ppos.first)+2][(ppos.second)-1] == '#' || theboard[(ppos.first)+2][(ppos.second)+1] == '#')){
				if(DEBUG_VALIDATEMOVE == 1 && true) { DEBUG(cout << "This move would push the box into a corner! Not OK." << endl); }

				ok = false;
			}
			if(wallCheck(c)){
				DEBUG(cout << "wall!!!" << endl);
				ok = false;
			}
		}
		if(DEBUG_VALIDATEMOVE == 1 && true) { DEBUG(cout << "There is no box in the way." << endl); }

		if(theboard[(ppos.first)+1][ppos.second] == '#'){
			if(DEBUG_VALIDATEMOVE == 1 && true) { DEBUG(cout << "You are trying to go into a wall. Not OK." << endl); }

			ok = false;
		}
	}

	else if(c == 'L') {
		if(theboard[ppos.first][(ppos.second)-1] == '$' || theboard[ppos.first][(ppos.second)-1] == '*') {
			if(DEBUG_VALIDATEMOVE == 1 && true) { DEBUG(cout << "Box will be affected." << endl); }

			if(theboard[ppos.first][(ppos.second)-2] == '#' || theboard[ppos.first][(ppos.second)-2] == '$'){
				if(DEBUG_VALIDATEMOVE == 1 && true) { DEBUG(cout << "This move would push the box into something! Not OK." << endl); }

				ok = false;
			}
			else if(theboard[ppos.first][ppos.second-2] == ' ' && theboard[(ppos.first)][ppos.second-3] == '#' && (theboard[(ppos.first)-1][(ppos.second)-2] == '#' || theboard[(ppos.first)+1][(ppos.second)-2] == '#')){
				if(DEBUG_VALIDATEMOVE == 1 && true) { DEBUG(cout << "This move would push the box into a corner! Not OK." << endl); }

				ok = false;
			}
			if(wallCheck(c)){
				DEBUG(cout << "wall!!!" << endl);
				ok = false;
			}
		}
		if(DEBUG_VALIDATEMOVE == 1 && true) { DEBUG(cout << "There is no box in the way." << endl); }

		if(theboard[ppos.first][(ppos.second)-1] == '#'){
			if(DEBUG_VALIDATEMOVE == 1 && true) { DEBUG(cout << "You are trying to go into a wall. Not OK." << endl); }

			ok = false;
		}
	}

	else if(c == 'R') {
		if(theboard[ppos.first][(ppos.second)+1] == '$' || theboard[ppos.first][(ppos.second)+1] == '*') {
			if(DEBUG_VALIDATEMOVE == 1 && true) { DEBUG(cout << "Box will be affected." << endl); }

			if(theboard[ppos.first][(ppos.second)+2] == '#' || theboard[ppos.first][(ppos.second)+2] == '$'){
				if(DEBUG_VALIDATEMOVE == 1 && true) { DEBUG(cout << "This move would push the box into something! Not OK." << endl); }

				ok = false;
			}
			else if(theboard[(ppos.first)][ppos.second+2] == ' ' && theboard[ppos.first][ppos.second+3] == '#' && (theboard[(ppos.first)-1][ppos.second+2] == '#' || theboard[ppos.first+1][ppos.second+2] == '#')){
				if(DEBUG_VALIDATEMOVE == 1 && true) { DEBUG(cout << "This move would push the box into a corner! Not OK." << endl); }

				ok = false;
			}
			if(wallCheck(c)){
				DEBUG(cout << "wall!!!" << endl);
				ok = false;
			}
		}
		if(DEBUG_VALIDATEMOVE == 1 && true) { DEBUG(cout << "There is no box in the way." << endl); }

		if(theboard[ppos.first][(ppos.second)+1] == '#'){
			if(DEBUG_VALIDATEMOVE == 1 && true) { DEBUG(cout << "You are trying to go into a wall. Not OK." << endl); }

			ok = false;
		}
	}

	if(DEBUG_VALIDATEMOVE == 1 && true) { DEBUG(cout << "Status at end: " << ok << endl); }

	return ok;
}

/* validateMove skall alltid anropas fore move().
 *
 * if(b.validateMove(m) {
 * 	b.move(m)
 * }
 */
pair<char, bool> board::move(char c) {

	if(DEBUG_MOVE == 1 && false) { DEBUG(cout << "move() input: " << c << endl); }

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
		if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "Input was: U" << endl); }
		// Kolla om vi p�verkar en l�da.
		if(theboard[(ppos.first)-1][ppos.second] == '$' || theboard[(ppos.first)-1][ppos.second] == '*') {
			if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "U: Box was hit by player!" << endl); }

			boxaffected = true;

			// Kolla om spelaren skjuter in en l�da i goalsquare-omr�det
			if(theboard[(ppos.first)-2][ppos.second] == '.'  && theboard[(ppos.first)-1][ppos.second] == '$'
					&& theboard[ppos.first][ppos.second] == '@') {
				if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "U: Player moves a box into goal square area." << endl); }
				theboard[(ppos.first)-2][ppos.second] = '*';
				theboard[(ppos.first)-1][ppos.second] = '@';
				theboard[ppos.first][ppos.second] = ' ';
			}
			// Kolla om spelaren skjuter in en l�da i goalsquare-omr�det och �ker med in.
			if(theboard[(ppos.first)-2][ppos.second] == '.'  && theboard[(ppos.first)-1][ppos.second] == '*'
					&& theboard[ppos.first][ppos.second] == '@') {
				if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "U: Player moves a box into goal square area and enters goal square." << endl); }
				theboard[(ppos.first)-2][ppos.second] = '*';
				theboard[(ppos.first)-1][ppos.second] = '+';
				theboard[ppos.first][ppos.second] = ' ';
			}
			// Kolla om spelaren skjuter en l�da inom goalsquare-omr�det
			if(theboard[(ppos.first)-2][ppos.second] == '.'  && theboard[(ppos.first)-1][ppos.second] == '*'
					&& theboard[ppos.first][ppos.second] == '+') {
				if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "U: Player moves a box within goal square area." << endl); }
				theboard[(ppos.first)-2][ppos.second] = '*';
				theboard[(ppos.first)-1][ppos.second] = '+';
				theboard[ppos.first][ppos.second] = '.';
			}
			// Kolla om spelaren skjuter en l�da inom goalsquare-omr�det
			if(theboard[(ppos.first)-2][ppos.second] == ' '  && theboard[(ppos.first)-1][ppos.second] == '*'
					&& theboard[ppos.first][ppos.second] == '+') {
				if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "U: Player moves a box within goal square area." << endl); }
				theboard[(ppos.first)-2][ppos.second] = '$';
				theboard[(ppos.first)-1][ppos.second] = '+';
				theboard[ppos.first][ppos.second] = '.';
			}
			// Kolla om spelaren skjuter en l�da som ligger vid kanten till goalsquare-omr�det
			if(theboard[(ppos.first)-2][ppos.second] == ' '  && theboard[(ppos.first)-1][ppos.second] == '$'
					&& theboard[ppos.first][ppos.second] == '+') {
				if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "U: Player moves a box at the border of goal square area." << endl); }
				theboard[(ppos.first)-2][ppos.second] = '$';
				theboard[(ppos.first)-1][ppos.second] = '@';
				theboard[ppos.first][ppos.second] = '.';
			}
			// Kolla om vi skjuter runt l�dan p� det vanliga golvet.
			if(theboard[(ppos.first)-1][ppos.second] == '$' || theboard[ppos.first][ppos.second] == '@') {
				if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "U: Player moves a box outside of goal squares." << endl); }
				theboard[(ppos.first-2)][ppos.second] = '$';
				theboard[(ppos.first-1)][ppos.second] = '@';
				theboard[ppos.first][ppos.second] = ' ';
			}
		}

		// Kolla om spelarmark�ren g�r in i goalsquare och ska byta mark�r till +.
		else if(theboard[(ppos.first)-1][ppos.second] == '.'  && theboard[ppos.first][ppos.second] == '@' && !boxaffected) {
			if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "U: Player enters a goal square." << endl); }
			theboard[(ppos.first)-1][ppos.second] = '+';
			theboard[ppos.first][ppos.second] = ' ';
		}
		// Kolla om spelarmark�ren redan var i goal square och l�gg tillbaka en . bakom spelaren.
		else if(theboard[(ppos.first)-1][ppos.second] == '.'  && theboard[ppos.first][ppos.second] == '+' && !boxaffected) {
			if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "U: Player moves from one goal square to another." << endl); }
			theboard[(ppos.first)-1][ppos.second] = '+';
			theboard[ppos.first][ppos.second] = '.';
		}
		// Kolla om spelarmark�ren l�mnar goal square omr�det. Tillbaka till @ allts�.
		else if(theboard[(ppos.first)-1][ppos.second] == ' '  && theboard[ppos.first][ppos.second] == '+' && !boxaffected) {
			if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "U: Player moves from one goal square to regular area." << endl); }
			theboard[(ppos.first)-1][ppos.second] = '@';
			theboard[ppos.first][ppos.second] = '.';
		}
		else { // Om vi inte p�verkar l�dan.
			if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "U: Player just moves in the regular floor area." << endl); }
			theboard[((ppos.first)-1)][ppos.second] = '@';
			theboard[ppos.first][ppos.second] = ' ';
		}
		ppos = make_pair((ppos.first-1), ppos.second); // Nya spelarpositionen p� br�dan.
	}

	/* D D D D D D D D D D D D D D D D D D D D D */

	if(c == 'D') {
		if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "Input was: D" << endl); }
		// Kolla om vi p�verkar en l�da.
		if(theboard[(ppos.first)+1][ppos.second] == '$' || theboard[(ppos.first)+1][ppos.second] == '*') {
			if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "D: Box was hit by player!" << endl); }

			boxaffected = true;

			// Kolla om spelaren skjuter in en l�da i goalsquare-omr�det
			if(theboard[(ppos.first)+2][ppos.second] == '.'  && theboard[(ppos.first)+1][ppos.second] == '$'
					&& theboard[ppos.first][ppos.second] == '@') {
				if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "D: Player moves a box into goal square area." << endl); }
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
				if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "D: Player moves a box at the border of goal square area." << endl); }
				theboard[(ppos.first)+2][ppos.second] = '$';
				theboard[(ppos.first)+1][ppos.second] = '@';
				theboard[ppos.first][ppos.second] = '.';
			}
			// Kolla om vi skjuter runt l�dan p� det vanliga golvet.
			if(theboard[(ppos.first)+1][ppos.second] == '$' || theboard[ppos.first][ppos.second] == '@') {
				if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "D: Player moves a box outside of goal squares." << endl); }
				theboard[(ppos.first+2)][ppos.second] = '$';
				theboard[(ppos.first+1)][ppos.second] = '@';
				theboard[ppos.first][ppos.second] = ' ';
			}
		}

		// Kolla om spelarmark�ren g�r in i goalsquare och ska byta mark�r till +.
		else if(theboard[(ppos.first)+1][ppos.second] == '.'  && theboard[ppos.first][ppos.second] == '@' && !boxaffected) {
			if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "D: Player enters a goal square." << endl); }
			theboard[(ppos.first)+1][ppos.second] = '+';
			theboard[ppos.first][ppos.second] = ' ';
		}
		// Kolla om spelarmark�ren redan var i goal square och l�gg tillbaka en . bakom spelaren.
		else if(theboard[(ppos.first)+1][ppos.second] == '.'  && theboard[ppos.first][ppos.second] == '+' && !boxaffected) {
			if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "D: Player moves from one goal square to another." << endl); }
			theboard[(ppos.first)+1][ppos.second] = '+';
			theboard[ppos.first][ppos.second] = '.';
		}
		// Kolla om spelarmark�ren l�mnar goal square omr�det. Tillbaka till @ allts�.
		else if(theboard[(ppos.first)+1][ppos.second] == ' '  && theboard[ppos.first][ppos.second] == '+' && !boxaffected) {
			if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "D: Player moves from one goal square to regular area." << endl); }
			theboard[(ppos.first)+1][ppos.second] = '@';
			theboard[ppos.first][ppos.second] = '.';
		}
		else { // Om vi inte p�verkar l�dan.
			if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "D: Player just moves in the regular floor area." << endl); }
			theboard[((ppos.first)+1)][ppos.second] = '@';
			theboard[ppos.first][ppos.second] = ' ';
		}
		ppos = make_pair((ppos.first+1), ppos.second); // Nya spelarpositionen p� br�dan.
	}

	/* L L L L L L L L L L L L L L L L L L L L */

	if(c == 'L') {
		if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "Input was: L" << endl); }
		// Kolla om vi p�verkar en l�da.
		if(theboard[ppos.first][ppos.second-1] == '$' || theboard[ppos.first][ppos.second-1] == '*') {
			if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "L: Box was hit by player!" << endl); }

			boxaffected = true;

			// Kolla om spelaren skjuter in en l�da i goalsquare-omr�det
			if(theboard[ppos.first][ppos.second-2] == '.'  && theboard[ppos.first][ppos.second-1] == '$'
					&& theboard[ppos.first][ppos.second] == '@') {
				if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "L: Player moves a box into goal square area." << endl); }
				theboard[ppos.first][ppos.second-2] = '*';
				theboard[ppos.first][ppos.second-1] = '@';
				theboard[ppos.first][ppos.second] = ' ';
			}
			// Kolla om spelaren skjuter in en l�da i goalsquare-omr�det och �ker med in.
			if(theboard[ppos.first][ppos.second-2] == '.'  && theboard[ppos.first][ppos.second-1] == '*'
					&& theboard[ppos.first][ppos.second] == '@') {
				if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "L: Player moves a box into goal square area and enters goal square." << endl); }
				theboard[ppos.first][ppos.second-2] = '*';
				theboard[ppos.first][ppos.second-1] = '+';
				theboard[ppos.first][ppos.second] = ' ';
			}
			// Kolla om spelaren skjuter en l�da inom goalsquare-omr�det
			if(theboard[ppos.first][ppos.second-2] == '.'  && theboard[ppos.first][ppos.second-1] == '*'
					&& theboard[ppos.first][ppos.second] == '+') {
				if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "L: Player moves a box within goal square area." << endl); }
				theboard[ppos.first][ppos.second-2] = '*';
				theboard[ppos.first][ppos.second-1] = '+';
				theboard[ppos.first][ppos.second] = '.';
			}
			// Kolla om spelaren skjuter en l�da ut fr�n goalsquare-omr�det
			if(theboard[ppos.first][ppos.second-2] == ' '  && theboard[ppos.first][ppos.second-1] == '*'
					&& theboard[ppos.first][ppos.second] == '+') {
				if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "L: Player moves a box within goal square area." << endl); }
				theboard[ppos.first][ppos.second-2] = '$';
				theboard[ppos.first][ppos.second-1] = '+';
				theboard[ppos.first][ppos.second] = '.';
			}
			// Kolla om spelaren skjuter en l�da som ligger vid kanten till goalsquare-omr�det
			if(theboard[ppos.first][ppos.second-2] == ' '  && theboard[ppos.first][ppos.second-1] == '$'
					&& theboard[ppos.first][ppos.second] == '+') {
				if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "L: Player moves a box at the border of goal square area." << endl); }
				theboard[ppos.first][ppos.second-2] = '$';
				theboard[ppos.first][ppos.second-1] = '@';
				theboard[ppos.first][ppos.second] = '.';
			}
			// Kolla om vi skjuter runt l�dan p� det vanliga golvet.
			if(theboard[ppos.first][ppos.second-1] == '$' || theboard[ppos.first][ppos.second] == '@') {
				if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "L: Player moves a box outside of goal squares." << endl); }
				theboard[(ppos.first)][ppos.second-2] = '$';
				theboard[(ppos.first)][ppos.second-1] = '@';
				theboard[ppos.first][ppos.second] = ' ';
			}
		}

		// Kolla om spelarmark�ren g�r in i goalsquare och ska byta mark�r till +.
		else if(theboard[ppos.first][ppos.second-1] == '.'  && theboard[ppos.first][ppos.second] == '@' && !boxaffected) {
			if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "L: Player enters a goal square." << endl); }
			theboard[ppos.first][ppos.second-1] = '+';
			theboard[ppos.first][ppos.second] = ' ';
		}
		// Kolla om spelarmark�ren redan var i goal square och l�gg tillbaka en . bakom spelaren.
		else if(theboard[ppos.first][ppos.second-1] == '.'  && theboard[ppos.first][ppos.second] == '+' && !boxaffected) {
			if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "L: Player moves from one goal square to another." << endl); }
			theboard[ppos.first][ppos.second-1] = '+';
			theboard[ppos.first][ppos.second] = '.';
		}
		// Kolla om spelarmark�ren l�mnar goal square omr�det. Tillbaka till @ allts�.
		else if(theboard[ppos.first][ppos.second-1] == ' '  && theboard[ppos.first][ppos.second] == '+' && !boxaffected) {
			if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "L: Player moves from one goal square to regular area." << endl); }
			theboard[ppos.first][ppos.second-1] = '@';
			theboard[ppos.first][ppos.second] = '.';
		}
		else { // Om vi inte p�verkar l�dan.
			if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "L: Player just moves in the regular floor area." << endl); }
			theboard[(ppos.first)][ppos.second-1] = '@';
			theboard[ppos.first][ppos.second] = ' ';
		}
		ppos = make_pair((ppos.first), ppos.second-1); // Nya spelarpositionen p� br�dan.
	}

	/* R R R R R R R R R R R R R R R R R R R R */

	if(c == 'R') {
		if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "Input was: R" << endl); }
		// Kolla om vi p�verkar en l�da.
		if(theboard[ppos.first][ppos.second+1] == '$' || theboard[ppos.first][ppos.second+1] == '*') {
			if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "R: Box was hit by player!" << endl); }

			boxaffected = true;

			// Kolla om spelaren skjuter in en l�da i goalsquare-omr�det
			if(theboard[ppos.first][ppos.second+2] == '.'  && theboard[ppos.first][ppos.second+1] == '$'
					&& theboard[ppos.first][ppos.second] == '@') {
				if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "R: Player moves a box into goal square area." << endl); }
				theboard[ppos.first][ppos.second+2] = '*';
				theboard[ppos.first][ppos.second+1] = '@';
				theboard[ppos.first][ppos.second] = ' ';
			}
			// Kolla om spelaren skjuter in en l�da i goalsquare-omr�det och �ker med in.
			if(theboard[ppos.first][ppos.second+2] == '.'  && theboard[ppos.first][ppos.second+1] == '*'
					&& theboard[ppos.first][ppos.second] == '@') {
				if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "R: Player moves a box into goal square area and enters goal square." << endl); }
				theboard[ppos.first][ppos.second+2] = '*';
				theboard[ppos.first][ppos.second+1] = '+';
				theboard[ppos.first][ppos.second] = ' ';
			}
			// Kolla om spelaren skjuter en l�da inom goalsquare-omr�det
			if(theboard[ppos.first][ppos.second+2] == '.'  && theboard[ppos.first][ppos.second+1] == '*'
					&& theboard[ppos.first][ppos.second] == '+') {
				if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "R: Player moves a box within goal square area." << endl); }
				theboard[ppos.first][ppos.second+2] = '*';
				theboard[ppos.first][ppos.second+1] = '+';
				theboard[ppos.first][ppos.second] = '.';
			}
			// Kolla om spelaren skjuter en l�da ut fr�n goalsquare-omr�det
			if(theboard[ppos.first][ppos.second+2] == ' '  && theboard[ppos.first][ppos.second+1] == '*'
					&& theboard[ppos.first][ppos.second] == '+') {
				if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "R: Player moves a box within goal square area." << endl); }
				theboard[ppos.first][ppos.second+2] = '$';
				theboard[ppos.first][ppos.second+1] = '+';
				theboard[ppos.first][ppos.second] = '.';
			}
			// Kolla om spelaren skjuter en l�da som ligger vid kanten till goalsquare-omr�det
			if(theboard[ppos.first][ppos.second+2] == ' '  && theboard[ppos.first][ppos.second+1] == '$'
					&& theboard[ppos.first][ppos.second] == '+') {
				if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "R: Player moves a box at the border of goal square area." << endl); }
				theboard[ppos.first][ppos.second+2] = '$';
				theboard[ppos.first][ppos.second+1] = '@';
				theboard[ppos.first][ppos.second] = '.';
			}
			// Kolla om vi skjuter runt l�dan p� det vanliga golvet.
			if(theboard[ppos.first][ppos.second+1] == '$' || theboard[ppos.first][ppos.second] == '@') {
				if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "R: Player moves a box outside of goal squares." << endl); }
				theboard[(ppos.first)][ppos.second+2] = '$';
				theboard[(ppos.first)][ppos.second+1] = '@';
				theboard[ppos.first][ppos.second] = ' ';
			}
		}

		// Kolla om spelarmark�ren g�r in i goalsquare och ska byta mark�r till +.
		else if(theboard[ppos.first][ppos.second+1] == '.'  && theboard[ppos.first][ppos.second] == '@' && !boxaffected) {
			if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "R: Player enters a goal square." << endl); }
			theboard[ppos.first][ppos.second+1] = '+';
			theboard[ppos.first][ppos.second] = ' ';
		}
		// Kolla om spelarmark�ren redan var i goal square och l�gg tillbaka en . bakom spelaren.
		else if(theboard[ppos.first][ppos.second+1] == '.'  && theboard[ppos.first][ppos.second] == '+' && !boxaffected) {
			if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "R: Player moves from one goal square to another." << endl); }
			theboard[ppos.first][ppos.second+1] = '+';
			theboard[ppos.first][ppos.second] = '.';
		}
		// Kolla om spelarmark�ren l�mnar goal square omr�det. Tillbaka till @ allts�.
		else if(theboard[ppos.first][ppos.second+1] == ' '  && theboard[ppos.first][ppos.second] == '+' && !boxaffected) {
			if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "R: Player moves from one goal square to regular area." << endl); }
			theboard[ppos.first][ppos.second+1] = '@';
			theboard[ppos.first][ppos.second] = '.';
		}
		else { // Om vi inte p�verkar l�dan.
			if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "R: Player just moves in the regular floor area." << endl); }
			theboard[(ppos.first)][ppos.second+1] = '@';
			theboard[ppos.first][ppos.second] = ' ';
		}
		ppos = make_pair((ppos.first), ppos.second+1); // Nya spelarpositionen p� br�dan.
	}

	solution.push_back(make_pair(c, boxaffected));

	if(DEBUG_MOVE == 1 && true) { DEBUG(cout << "move() result:" << endl; /* printBoard() */); }

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

bool board::solve() {

	char moves[]= {'D','R','U', 'L', 0};
	int i=0;
	string m;

	DEBUG(getline(cin, m, '\n'));
	visited_boards.push_back(theboard);
#if USE_HASH
	visited_hashed_boards.push_back(getHash(theboard));
#endif
	while(1) {
		for(i; moves[i];) {
				nodes_checked++;
				check_100 = (++check_100) % 100;
				if(!check_100) {
					gettimeofday(&time, 0);
					if(time.tv_sec > second_checked) {
						second_checked = time.tv_sec;
						cout << "nodes checked last second: " << nodes_checked - nodes_checked_last_time << "\n";
						nodes_checked_last_time = nodes_checked;
					}
				}
				if(validateMove(moves[i])) {
				move(moves[i]);
				printBoard();
#if USE_REACH
				if( reachableBoardVisited()) {
#else
				if( currentBoardVisited()) {
#endif
					//add the board just so we can remove a board in the backtracking step
					visited_boards.push_back(theboard);
#if USE_HASH
					visited_hashed_boards.push_back(getHash(theboard));
#endif
					DEBUG(cout << "wrong move '" << moves[i] << "' made, board already visited, backtracking---------------------\n");
					break; //backtrack
				}
				if(goalTest()) {
					cout << "We found a solution!!--------------\nsolution = "
							<< generate_answer_string() << endl << "nodes checked = " << nodes_checked << endl;
					gettimeofday(&time, 0);
					cout << "seconds: " << time.tv_sec - time_begin.tv_sec << "." <<
							time.tv_usec - time_begin.tv_usec << "\n";
					return true;
				}
				visited_boards.push_back(theboard);
#if USE_HASH
				visited_hashed_boards.push_back(getHash(theboard));
#endif
				i = 0;
				DEBUG(getline(cin, m, '\n'));
			} else {
				DEBUG(cout << "Move was not allowed" << endl);
				i++;
			}

		}
		//backtracking
		while(1) {
			pair<char, bool> last_move = solution.back();
			solution.pop_back();
			moveBack(last_move);
			DEBUG(cout << "after backtracking including moveBack the board looks like:\n");
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
	return false;
}

bool board::reachableBoardVisited() {
	int i, result;
	char moves[]= {'D','R','U', 'L', 0};
	pair<char, bool> last_move2, last_move = solution.back();

	vector< vector<char> > backup_board;
	backup_board = theboard; //the board is yet not on the visited boards list

	if(currentBoardVisited())
		return 1; //check current pos first

	DEBUG(cout << "current pos checked, need also to check 3 reachable states......\n");

	//check 3 reachable positions

	for(i=0; moves[i]; i++) {
		//don't check where we came from
		switch(last_move.first) {
		case 'U':
			if(moves[i] == 'D')
				continue;
			break;
		case 'D':
			if(moves[i] == 'U')
				continue;
			break;
		case 'L':
			if(moves[i] == 'R')
				continue;
			break;
		case 'R':
			if(moves[i] == 'L')
				continue;
			break;
		}

		DEBUG(cout << "will check " << moves[i] << '\n');

		if(validateMove(moves[i])) {
			move(moves[i]);
			result = currentBoardVisited();
			visited_boards.push_back(theboard); //Just so that moveback can remove something..
#if USE_HASH
			visited_hashed_boards.push_back(getHash(theboard));
#endif
			DEBUG(cout << "pushing back this board:\n");
			printBoard();
			last_move2 = solution.back();
			solution.pop_back();
			moveBack(last_move2);
			theboard = backup_board;
			DEBUG(cout << "result of checking reachable state " << moves[i] << " was " << result << '\n');
			if(result)
				return 1;
		}
	}
	DEBUG(cout << "status of board after reachable state checking:\n");
	printBoard();
	return 0;
}


bool board::currentBoardVisited() {
	int i;

#if USE_HASH
	long hash = getHash(theboard);
	for(i = 0; i < visited_hashed_boards.size(); i++) {
		if(hash == visited_hashed_boards[i])
			return 1;
	}
#else
	for(i = 0; i < visited_boards.size(); i++) {
		if(theboard == visited_boards[i])
			return 1;
	}
#endif
	return 0;
}

string board::generate_answer_string() {
	int i;
	string result;

	for(i=0; i < solution.size(); i++) {
		result += solution[i].first;
		result += " ";
	}
	return result;
}
