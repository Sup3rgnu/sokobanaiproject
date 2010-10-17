/* 
 * File:   board.h
 * Author: Voddlerdoods
 *
 * Created on September 21, 2010, 3:00 PM
 */
#ifndef BOARD_H
#define	BOARD_H

#define DEBUG_ALL		0
#define DEBUG_HASHTABLE 0
#define USE_HASHTABLE	0
#define USE_TR1_HASH	0
#define USE_WALL		0
#define USE_REACH		0
#define USE_STICK		0

#include <string>
#include <vector>
#include <utility>
#include <sys/time.h>
#if USE_HASHTABLE
#include <ext/hash_map> // non STL
#endif
#include <unordered_map>

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
    string getHash();
    void prepareBoard();
    pair<int, int> goalDistance();
    int printhash();
    bool stickToBox(char);
    void addVisitedState();
    bool checkVisitedState();
    void delVisitedState();
    string theboardToString();
    void getLastState();
private:

    char currentMove;						// Det move vi just nu beaktar. Skall vara VERSAL.
    pair<int, int> ppos;					// ppos h�ller spelarmark�rens aktuella position p� br�dan.
    pair<int, int>  distance;
    pair<char, bool> move_result;			// Varje move genererar en riktning U/D/L/R samt talar om ifall en l�da p�verkats.
    vector< pair <char, bool> > solution;	// Vektorn h�ller samtliga aktuella move_result pairs.
    vector< vector<char> > theboard;		// Arren blev en vektor.
    vector< vector<char> > theboardLayer;
    vector< vector< vector<char> > > visited_boards;
    unsigned long long nodes_checked;
    struct timeval time_begin, time;
    int second_checked;
    int check_100;
    int nodes_checked_last_time;
#if USE_HASHTABLE
    __gnu_cxx::hash_multimap<unsigned long int, vector < vector< char > > > visited_states;
    vector<unsigned long int> hkey_history;
#endif
#if USE_TR1_HASH
    typedef std::unordered_map<string, int> myHash;
    myHash hashTable;
    vector< string > visited_hashes;
    string thehash;
#endif
};

#endif	/* BOARD_H */

