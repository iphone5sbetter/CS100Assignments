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

        //std::string toLowerCase(std::string strToConvert);

    private:
        //create the alphaTrie
        alphaTrie* t;
        string** board; // do we need this?
        unsigned int col;
        unsigned int row;
        bool buildCalled = false;
        bool setCalled = false;
        vector<int> location;
       
        //void dealWithTrie(alphaNode *node, string word, int length, int minLength, set<string>* words);
        void findMoreWords(int r, int c, string word, bool** visited, set<string>* words, alphaNode *node, unsigned int length );
        int findNextChar( int x, int y, string word, bool **used);
};

class BogglePiece {
        vector<BogglePiece> adjacentPieces;

    public:
        string str;
        int index;
        int row;
        int col;

        BogglePiece() {

        }

        BogglePiece(string str) {
            this->str = str;
        }
        BogglePiece(string str, int row, int col) {
            this->str = str;
            this->row = row;
            this->col = col;
        }

        void addAdjacentPiece(BogglePiece piecePtr);
        vector<BogglePiece>getAdjacentPieces();
        
};

#endif //BOGGLEPLAYER_H
