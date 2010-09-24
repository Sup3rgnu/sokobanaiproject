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

using namespace std;

board::board (string board1){

	vector<string> vecstrtokens;
	int cols = 0;
	int rows = 0;
	int current = 0;
	stringstream ss(board1);
	string token;

	cout << board1 << endl;

	// Split input board string board1 into a string for each row
	// so we can count board row and width.
	while(getline(ss, token, '\n')) {
		current = token.size();
		if(current > cols) {
			cols = current;
		}
		vecstrtokens.push_back(token);
	}
	rows = vecstrtokens.size();

	//cout << "rows = " << rows << " cols = " << cols << '\n';

	// Load strings to 2d char array.
	char board[rows][cols];
	for (int i = 0; i < rows; i++) {
		const char *strp = vecstrtokens[i].c_str();
		int j = 0;
		while(*strp != '\0') {
			board[i][j++] = *strp++;
			}
	}

	// Print 2d char array.
	for(int i = 0; i < rows; i++) {
		cout << i+1 << "[";
		for(int j = 0; j < cols; j++) {
			cout << board[i][j] << ",";
		}
		cout << "]" << endl;
	}
}

bool goalTest() {

}

bool validateMove(char) {
	// Robert jobbar på denna.

}

pair<char, bool> move(char c) {
	// Robert jobbar på denna.

}

void updateBoard(pair<char, bool> m) {

}

void solve() {

}


