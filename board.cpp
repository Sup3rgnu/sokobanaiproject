
#include <iostream>
#include <sstream>
#include <vector>
#include "board.h"


board::board (std::string board1){

 std::vector< std::string > result;
 int cols, rows;

 std::stringstream ss(board1);
 std::string item;

 while(std::getline(ss, item, '\n')) {
    result.push_back(item);
 }

 std::cout << "rows = " << result.size() << '\n';


}


