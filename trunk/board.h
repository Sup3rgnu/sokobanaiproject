/* 
 * File:   board.h
 * Author: Voddlerdoods
 *
 * Created on September 21, 2010, 3:00 PM
 */
#ifndef BOARD_H
#define	BOARD_H

#include <string>
#include <vector>
#include <utility>

using namespace std;

class board{

public:

    board(string board);
    bool goalTest();
    bool validateMove(char);
    pair<char, bool> move(char);
    void updateBoard(pair <char, bool> m);
    void solve();

private:

    char currentMove;
    pair<char, bool> move_result;
    vector< pair <char, bool> > solution;
};

#endif	/* BOARD_H */

