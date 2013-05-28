#include "boggleplayer.h"

public:
/*
 * Takes as argument a set containing words specifying the official lexicon to be used. 
 * Each word in the set will be a string consisting of lowercase a-z only. Function must
 * load the words into an efficient datastructure that will be used internally as needed
 * by the BogglePlayer
 */
void BaseBogglePlayer::buildLexicon(const std::set<string>& word_list){
  set<string>:: const_iterator it = word_list.begin();
  set<string>:: const_iterator end = word_list.end();
  t = new alphaTrie();

  while(it != end){
   t->insert(it*);   //insert into t using alphaTrie's insert
   it++;
  }

}


/* Takes number of rows and columns in board, and an array of strings
 * representing what is shown on Boggle board.Elements of the vector specify
 * the contents of board in row major order. Function uses information
 * passed in to construct a data structure representing the board.
 */
void BaseBogglePlayer::setBoard(unsigned int rows, unsigned int cols, string** diceArray){
  
 board = new string*[rows];
 this -> row = rows;
 this -> col = cols;
   for(unsigned int r = 0; r < rows; r++){
    board[r] = new string[cols];           // need explanation
	for(unsigned int c = 0; c < columns; c++){
	 this->board[r][c] = diceArray[r][c];
	}
  }
}


/*
 * Takes an int specifying min word length, and a pointer to a ste of strings. Returns
 * false if setBoard() or buildLexicon() have not been called for this BogglePlayer. If they have,
 * it will return true after 
 *  1)Filling the set with words that are at least the given min length
 *  2) Are in lexicon specified by the most recent call to buildLexicon()
 *  3) Can be found following an acyclic simple path on the board 
 *     specified by the most recent call to setBoard()
 */
bool BaseBogglePlayer::getAllValidWords(unsigned int minimum_word_length, set<string>* words){


}




bool BaseBogglePlayer::isInLexicon(const string& word_to_check){


}



vector<int> BaseBogglePlayer::isOnBoard(const string& word_to_check){


}



void BaseBogglePlayer::getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols){


}

~BogglePlayer() {

}
