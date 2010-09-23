/* 
 * File:   board.h
 * Author: Voddlerdoods
 *
 * Created on September 21, 2010, 3:00 PM
 */

#include <string>

#ifndef BOARD_H
#define	BOARD_H

class board{

public:

    board(std::string board);
    boolean goalTest();
    boolean validateMove(char);
    boost::tuple move(char);
    void updateBoard(boost::tuple move);
    void solve();

private:
    
};

#endif	/* BOARD_H */

