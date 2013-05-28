#ifndef BOGGLEPLAYER_H
#define BOGGLEPLAYER_H

#include "baseboggleplayer.h"
#include "boggleutil.h"


class BogglePlayer: public BaseBogglePlayer {

public:
    void buildLexicon(const set<string>& word_list)  ;
    void BaseBogglePlayer::setBoard(unsigned int rows, unsigned int cols, string** diceArray)  ;
    bool BaseBogglePlayer::getAllValidWords(unsigned int minimum_word_length, set<string>* words)  ;
    bool BaseBogglePlayer::isInLexicon(const string& word_to_check)  ;
    vector<int> BaseBogglePlayer::isOnBoard(const string& word_to_check);
    void BaseBogglePlayer::getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols);

private:
    //create the alphaTrie
    alphaTrie* t;
    string** board; // do we need this?
    unsigned int col;
    unsigned int row;
};

#endif //BOGGLEPLAYER_H
