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
    buildCalled = true;
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
    board[r] = new string[cols];           // need explanation
	for(unsigned int c = 0; c < cols; c++){
	 this->board[r][c] = diceArray[r][c];
	}
  }

   setCalled = true;
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
bool BogglePlayer::getAllValidWords(unsigned int minimum_word_length, set<string>* words){

    // Return false if buildLexicon() or setBoard() hasn't been build yet

    // speed will change depending on if you call isInLexicon or isOnBoard first

    // Returns true after settin the set of words "words" (the param) with word that:
    //  - meet the minimum_word_length
    //  - are in the lexicon specified by the most recent call to buildLexicon()
    //  - can be found by an acyclical simple path on the board --- Hella hard part
    //  ^just call isOnBoard for the last part
}




bool BogglePlayer::isInLexicon(const string& word_to_check){
   
    //Find word_to_check in the alphaTrie
    if(t -> find(word_to_check)){
        return true;
    }

    // why not just return false here?

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



vector<int> BogglePlayer::isOnBoard(const string& word_to_check){
    queue<char> boardqueue;

    // If the param word_to_check is on the board, then return a vector of the positions of letters
    // in proper word order - R * Width + C
    
    // Return empty vector if the word is not on the board or if setBoard() hasn't been called yet
    if (setCalled == false)
        return NULL;
    
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < rows; i++) {
           boardqueue.add 
        }
    }
}



void BogglePlayer::getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols){


}
