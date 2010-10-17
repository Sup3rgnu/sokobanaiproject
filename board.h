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
#define USE_HASHTABLE	1
#define USE_TR1_HASH	0
#define USE_WALL		0
#define USE_REACH		1
#define USE_STICK		1
#define USE_5SEC_LIMIT	1
#define USE_AVOID_STATE_REP 0

#include <string>
#include <vector>
#include <utility>
#include <sys/time.h>
#if USE_HASHTABLE
#include <ext/hash_map> // non STL
#endif
#if USE_TR1_HASH
#include <unordered_map>
#endif

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
    void prepareBoard();
    pair<int, int> goalDistance();
    int printhash();
    bool stickToBox(char);
    void addVisitedState();
    bool checkVisitedState();
    void delVisitedState();
    void getLastState();
private:

    char currentMove;						// Current move, capital U/L/D/R.
    pair<int, int> ppos;					// keeps player marker position on board.
    pair<int, int>  distance;
    pair<char, bool> move_result;			// Each move generates a direction U/D/L/R and stores a bool on if a box was affected.
    vector< pair <char, bool> > solution;	// Vector that keeps all current move_result pairs.
    vector< vector<char> > theboard;		// Vector of vector of char that holds the current board.
    vector< vector<char> > theboardLayer;
    vector< vector< vector<char> > > visited_boards; 	// Holds visited states for our poor first implementation of repeated states detection.
    unsigned long long nodes_checked;			// For timing and stats
    struct timeval time_begin, time;
    int second_checked;
    int check_100;
    int nodes_checked_last_time;
#if USE_HASHTABLE
    string theboardToString();				// returns string from board vector
    __gnu_cxx::hash_multimap<unsigned long int, vector < vector< char > > > visited_states;	// hash map
    vector<unsigned long int> hkey_history;	// keep track of hkeys added so we can backtrack when needed
    string boardstr;						// keep a copy of the board as a string
    unsigned long int hkey;					// current boards hkey
    vector< vector<char> > previousboard;
#endif
#if USE_TR1_HASH
    typedef long hashType;
    typedef std::unordered_map<hashType, int> hashTableType;
    hashTableType hashTable;
    vector< hashType > visited_hashes;
    hashType thehash;
    hashType getHash();
    string getBoardString();
    #endif
};

#endif	/* BOARD_H */

