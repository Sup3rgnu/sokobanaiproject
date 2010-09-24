/*
 * stdin_client.cpp
 *
 *  Created on: Sep 23, 2010
 *      Author: Robert
 *
 *      usage: $ cat levelX.sok | ./stdin_client
 *
 *      for easier testing of different boards.
 */

#include <iostream>
#include <string>
#include "board.h"

using namespace std;

int main() {

	string s1;
	char c;

	while(true) {
		cin.get(c);
		if(!cin.eof()) {
		s1 += c;
		}
		else
			break;
	}

	board b1(s1);

	/* Robert som bygger sina medlemsfunktioner och kör lite blaj som kan tas bort om man vill */
	b1.printBoard();
	//b1.move('U');

	/* slut på blajjet */

	return 0;
}
