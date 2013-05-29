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
        vector<int> isOnBoard(const string& word_to_check)  ;
        void getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols)  ;
<<<<<<< HEAD
      
    private:
        //create the alphaTrie
        alphaTrie* t;
        string** board;
        vector<int> location;
=======

    private:
        //create the alphaTrie
        alphaTrie* t;
        string** board; // do we need this?
>>>>>>> 8c5c479724cc6abe3f8502fbfc079707afbbfe69
        unsigned int col;
        unsigned int row;
        bool buildCalled = false;
        bool setCalled = false;
<<<<<<< HEAD
 	vector<string> used;
       
        int findNextChar( int x, int y, string word, vector<string> used);
=======
>>>>>>> 8c5c479724cc6abe3f8502fbfc079707afbbfe69
};

#endif //BOGGLEPLAYER_H
