#include <iostream>
#include <string>
#include <iostream>
#include "board.h"

using namespace std;

int main(int argc, char *arv[]) {

	std::string s1 = "########\n#......#\n#@$##$ #\n#  ##  #\n# $$ $$#\n#      #\n#   #  #\n########\n";
	board b1(s1);
	cout << (b1.goalTest() ? "Solved" : "Not solved") << endl;

	b1.printBoard();

	if(argc > 1) {
		cout << "running solve\n";
		b1.solve();
		return 0;
	}

	/* Kod f�r att spela med tangentbordet */
	string m;
	while(true) {

		getline(cin, m, '\n');
		if(b1.validateMove(m.at(0)))
			b1.move(m.at(0));

		else {
			cout << "Move not allowed, please try again." << endl;
			b1.printBoard();
		}
		b1.printBoard();
	}
	/* tangentbord */

	return 0;
}
