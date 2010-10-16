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
#include <sys/time.h>

using namespace std;

class board{

public:

    board(string board);
    bool goalTest();
    bool wallCheck(char);
    bool validateMove(char);
    pair<char, bool> move(char);
    void moveBack(pair<char, bool>);
    void updateBoard(pair <char, bool> m);
    bool solve();
    void printBoard();
    bool currentBoardVisited();
    bool reachableBoardVisited();
    bool compareBoardToCurrent(vector< vector<char> >);
    string generate_answer_string();
    long getHash();
    void prepareBoard();
private:

    char currentMove;						// Det move vi just nu beaktar. Skall vara VERSAL.
    pair<int, int> ppos;					// ppos h�ller spelarmark�rens aktuella position p� br�dan.
    pair<char, bool> move_result;			// Varje move genererar en riktning U/D/L/R samt talar om ifall en l�da p�verkats.
    vector< pair <char, bool> > solution;	// Vektorn h�ller samtliga aktuella move_result pairs.
    vector< vector<char> > theboard;		// Arren blev en vektor.
    vector< vector<char> > theboardLayer;
    vector< vector< vector<char> > > visited_boards;
    vector< long > visited_hashed_boards;
    long thehash;
    unsigned long long nodes_checked;
    struct timeval time_begin, time;
    int second_checked;
    int check_100;
    int nodes_checked_last_time;
};

#endif	/* BOARD_H */

