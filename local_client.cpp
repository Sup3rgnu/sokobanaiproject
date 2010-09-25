#include <iostream>
#include <string>
#include "board.h"

int main() {

	std::string s1 = "########\n#   # .#\n#   $$.#\n####   #\n   #@ ##\n   ####";
	board b1(s1);
	cout << (b1.goalTest() ? "Solved" : "Not solved") << endl;

	return 0;
}
