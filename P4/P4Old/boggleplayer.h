#ifndef BOGGLEPLAYER_H
#define BOGGLEPLAYER_H

#include "baseboggleplayer.h"
#include "boggleutil.h"


class BogglePlayer: public BaseBogglePlayer {

public:
    void buildLexicon(const set<string>& word_list)  ;
    void setBoard(unsigned int rows, unsigned int cols, string** diceArray)  ;
    bool getAllValidWords(unsigned int minimum_word_length, set<string>* words)  ;
    bool isInLexicon(const string& word_to_check)  ;
    vector<int> isOnBoard(const string& word_to_check);
    void getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols);

private:
    //create the alphaTrie
    alphaTrie* t;
    string** board; // do we need this?
    unsigned int col;
    unsigned int row;
};

#endif //BOGGLEPLAYER_H
