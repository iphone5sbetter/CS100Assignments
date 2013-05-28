#include "boggleplayer.h"
#include <queue>

/*
 * Takes as argument a set containing words specifying the official lexicon to be used. 
 * Each word in the set will be a string consisting of lowercase a-z only. Function must
 * load the words into an efficient datastructure that will be used internally as needed
 * by the BogglePlayer
 */
void BogglePlayer::buildLexicon(const std::set<string>& word_list){
  set<string>:: const_iterator it = word_list.begin();
  set<string>:: const_iterator end = word_list.end();
  this -> t = new alphaTrie();

  while(it != end){
   t->insert(*it);   //insert into t using alphaTrie's insert
   it++;
  }

}


/* Takes number of rows and columns in board, and an array of strings
 * representing what is shown on Boggle board.Elements of the vector specify
 * the contents of board in row major order. Function uses information
 * passed in to construct a data structure representing the board.
 */
void BogglePlayer::setBoard(unsigned int rows, unsigned int cols, string** diceArray){
  
 board = new string*[rows];
 this -> row = rows;
 this -> col = cols;
   for(unsigned int r = 0; r < rows; r++){
    board[r] = new string[cols];           //at board array, there's a array inside
	for(unsigned int c = 0; c < cols; c++){
	 this->board[r][c] = diceArray[r][c];
	}
  }
}


/*
 * Takes an int specifying min word length, and a pointer to a set of strings. Returns
 * false if setBoard() or buildLexicon() have not been called for this BogglePlayer. If they have,
 * it will return true after 
 *  1)Filling the set with words that are at least the given min length
 *  2) Are in lexicon specified by the most recent call to buildLexicon()
 *  3) Can be found following an acyclic simple path on the board 
 *     specified by the most recent call to setBoard()
 */
bool BogglePlayer::getAllValidWords(unsigned int minimum_word_length, set<string>* words){


}



/*
 * Determines whether word_to_check can be found in lexicon. Function returns true
 * if word is in lexicon, and returns false if it is not in lexicon or if
 * buildLexicon() has not yet been called.
 */
bool BogglePlayer::isInLexicon(const string& word_to_check){
    //Find word_to_check in the alphaTrie
    if(t -> find(word_to_check)){
        return true;
    }
    //If buildLexicon() has not been called and no alphaTrie has been made
    else if(t -> root == nullptr){
        return false;
    }
    //if word_to_check is not in lexicon
    else
    {
     return false;
    }
}


/*
 * Determines whether word_to_check can be found by following an acyclic
 * simple path on the board specified by the most recent call to setBoard().
 * If possible, the function returns a vector with integers specifying the locations
 * of dice that can be used to form the word, in the order that spells the word.
 * The integers used to specify the locations are row-major-order indices. If not
 * possible to form the word, or if setBoard() has not yet been called, function
 * returns an empty vector
 */
vector<int> BogglePlayer::isOnBoard(const string& word_to_check){
   // Use a recursive queue structure to check adjacencies in board. Make sure
   // to not include locations multiple times in queue structure. Start at every
   // location on board and enqueue that letter as well as neighboring letters.
   // Check if that letter or neighbors are in word_to_check.  If not, dequeue
   // that letter(or neighboring letters.  If it is in word_to_check, store that
   // coordinate in vector

   queue<char> boardq;


   

}



void BogglePlayer::getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols){


}


