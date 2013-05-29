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

<<<<<<< HEAD
// returns 1 if complete word is found, returns 0 if word not found
int BogglePlayer:: findNextChar( int x, int y, string word, vector<string> used){
     int flag;

     std:: string character = word.substr(0, 1);  //take next character

         //check if coordinate is on board
     if( x - 1 >= 0 ){
        //check if letter at x-1, y is next letter
        if( character == board[x-1][y] ){
            x--;  //char is found, so adjust coordinates for function call
            used.push_back( character );  //add character to vector
	    flag = findNextChar( x, y, word.substr( 1, word.length()-1), used ); //flag will be set when function returns
            //return flag here to signify if word was found?
        }
	else{
             flag = 0;  //character was not found in neighbors
        }
     } 

     //check if coordinate is on board
     if( x + 1 < this -> row ){
        //check if letter at x+1,y is next letter
        if( character == board[x+1][y] ){
            x++;  //char is found, so adjust coordinates for fn call
            used.push_back(character); //add character to vector
	    flag = findNextChar( x, y, word.substr( 1, word.length()-1), used ); //flag will be set when fn returns
            //return flag here to signify if word was found?            
        }
        else{
             flag = 0; //character not found in neighbors
        }
    }

    //check if coordinate is on board
    if( y - 1 >= 0 ){
       //check if letter at x,y-1 is next letter
       if( character == board[x][y-1] ){
           y--;  //char is found, so adjust coordinates for fn call
           used.push_back( character ); //add character to vector
           flag = findNextChar( x, y, word.substr( 1, word.length()-1), used ); //flag will be set when fn returns
           //return flag here to signify if word was found?
       }
       else{
            flag = 0;  //character not found in neighbors
       }
    }

    //check if coordinate is on board
    if( y + 1 < this -> col ){
       //check if letter at x, y+1 is next letter
       if( character == board[x][y+1] ){
           y++;  //char is found, so adjust coordinates for fn call
           used.push_back( character ); //add character to vector
           flag = findNextChar( x, y, word.substr( 1, word.length()-1), used ); //flag will be set when fn returns
           //return flag here to signify if word was found?
       }
       else{
            flag = 0; //character not found in neighbors
       }
    }
        
    //return the final result of flag?
    if( flag = 1 )
        return flag;
    else
       return flag;     
}
=======

>>>>>>> 8c5c479724cc6abe3f8502fbfc079707afbbfe69

vector<int> BogglePlayer::isOnBoard(const string& word_to_check){
    queue<char> boardqueue;
    vector<int> location;

    // If the param word_to_check is on the board, then return a vector of the positions of letters
    // in proper word order - R * Width + C
    
    // Return empty vector if the word is not on the board or if setBoard() hasn't been called yet
<<<<<<< HEAD
    if(setCalled == false)
        return location;
    
    int wordpos = 0;
    for (int j = 0; j < row; j++) {
        for (int i = 0; i < col; i++) {
             //check char from board and check first char of word_to_check
	            
	     std::string str = word_to_check.substr(0, 1); //start at index[0], only take one letter
             if( str == board[i][j]){
                 //If first char matches, call helper func
                int pos = findNextChar( i, j, word_to_check.substr(1, word_to_check.length() - 1), used );	
             }
=======
    if (setCalled == false)
        return location;
    
<<<<<<< HEAD
    for (int j = 0; j < row; j++) {
        for (int i = 0; i < col; i++) {
           boardqueue.push( board[i][j] );
=======
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < rows; i++) {
           boardqueue.add 
>>>>>>> 8c5c479724cc6abe3f8502fbfc079707afbbfe69
>>>>>>> 540bfdbbeff961c62aead8b765436a1eecb5f731
        }
    }
}



void BogglePlayer::getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols){


}
