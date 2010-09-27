#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include "board.h"

using namespace std;

int main(int argc, char *argv[]) {

	if(argc > 1) {
		string thefile, tmp;

		tmp = "boards/"; tmp += argv[1];
		ifstream input(tmp.c_str());

		while(!input.eof()) {
		    getline(input, tmp);
		    thefile += tmp;
		    thefile += "\n";
		}
		cout << "running solve\n";
		board b1(thefile);
		b1.solve();
		return 0;
	}

/*
	string s1 = "########\n#......#\n#@$##$ #\n#  ##  #\n# $$ $$#\n#      #\n#...#  #\n########\n";

	board b1(s1);

	// Kod f�r att spela med tangentbordet
	string m;
	while(true) {

		getline(cin, m, '\n');
		if(b1.validateMove(m.at(0)))
			b1.move(m.at(0));

		else {
			cout << "Move not allowed, please try again." << endl;
			b1.printBoard();
		}
		//b1.printBoard();
	}
*/
	return 0;
}
