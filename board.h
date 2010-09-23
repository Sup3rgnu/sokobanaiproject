/* 
 * File:   board.h
 * Author: Voddlerdoods
 *
 * Created on September 21, 2010, 3:00 PM
 */

#include <string>
#include <boost/tuple/tuple.hpp>

#ifndef BOARD_H
#define	BOARD_H

class board{

public:

    board(std::string board);
    bool goalTest();
    bool validateMove(char);
    boost::tuple<char,bool> move(char);
    void updateBoard(boost::tuple<char,bool> move);
    void solve();

private:
    
};

#endif	/* BOARD_H */

