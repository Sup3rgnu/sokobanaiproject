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
    void printBoard();

private:

    char currentMove;						// Det move vi just nu beaktar. Skall vara VERSAL.
    pair<int, int> ppos;					// ppos håller spelarmarkörens aktuella position på brädan.
    pair<char, bool> move_result;			// Varje move genererar en riktning U/D/L/R samt talar om ifall en låda påverkats.
    vector< pair <char, bool> > solution;	// Vektorn håller samtliga aktuella move_result pairs.
    vector< vector<char> > theboard;			// Arren blev en vektor.
};

#endif	/* BOARD_H */

