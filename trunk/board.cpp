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

const int DEBUG_MOVE = 1;

using namespace std;

board::board (string board1){

	stringstream ss(board1);
	string token;

	ppos = make_pair(3,3);
	vector<char> newrow;

	/* Läser indata via en stringstream och splittar på rad
	 * och sedan per char som stoppas i en 2d vector.
	 */
	while(getline(ss, token, '\n')) {

		const char *strp = token.c_str();

		while(*strp != '\0') {
			newrow.push_back(*strp++);
		}

		theboard.push_back(newrow);

		newrow.clear();
		token.clear();
	}

}

void board::printBoard() {

	cout << "printBoard()" << endl;
	for(int i = 0; i < theboard.size(); i++) {
		cout << i+1 << "[";
		for(int j = 0; j < theboard[i].size(); j++) {
			cout << theboard[i][j] << ",";
		}
		cout << "]" << endl;
	}

}

bool board::goalTest() {

}

bool board::validateMove(char) {
	// Robert jobbar på denna.

}

/* validateMove skall alltid anropas före move(). */
pair<char, bool> board::move(char c) {
	// Robert jobbar på denna.

}

void board::updateBoard(pair<char, bool> m) {

}

void board::solve() {

}


