
#include <iostream>
#include <sstream>
#include <vector>
#include "board.h"

board::board (std::string board1){

std::vector< std::string > result;
int cols = 0;
int rows = 0;
int current = 0;
 std::stringstream ss(board1);
 std::string item;

 while(std::getline(ss, item, '\n')) {
	current = item.size();
	if(current > cols) {
		cols = current;
	}
    result.push_back(item);
 }

 std::cout << "rows = " << result.size() << " cols = " << cols << '\n';


}


