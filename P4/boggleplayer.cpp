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
   t -> insert(*it);   //insert into t using alphaTrie's insert

   // Should test
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


// returns 1 if complete word is found, returns 0 if word not found
int BogglePlayer:: findNextChar( int j, int i, string word, bool **used){
     int flag = 0; 
     std::string character = word.substr(0, 1);  //take next character

     std::cout << "Find called with: " << j << " " << i << " " << word << " " << endl; 
     std::cout << "Looking for character: " << character << endl;
    
     used[j][i] = true;

    //TOP NEIGHBOR
     if( j - 1 >= 0 ){
        //check if letter at j-1, i is next letter
        if( character == board[j-1][i] )
        {
            if (used[j-1][i] != true) {
                location.push_back( (j-1) * col + i);
                j--;  //char is found, so adjust coordinates for function call
                // used.push_back( character );  //add character to vector
            
            
                if ( word.length() != 1) 
	                flag = findNextChar( j, i, word.substr( 1, word.length()-1), used ); //flag will be set when function returns
                else 
                    return 1;
            }
        }
     } 

     //BOTTOM NEIGHBOR
     if( j + 1 < this -> row ){
                 //check if letter at j+1,i is next letter
        if( character == board[j+1][i] ){
            j++;
            if (used[j][i] != true) {
                location.push_back( j * col + i);
                //j++;  //char is found, so adjust coordinates for fn call
                //used.push_back(character); //add character to vector

                if ( word.length() != 1) 
	                flag = findNextChar( j, i, word.substr( 1, word.length()-1), used ); //flag will be set when function returns
                else 
                    return 1;  
            }
        }
    }

    //LEFT NEIGHBOR
    if( i - 1 >= 0 ){
       //check if letter at j,i-1 is next letter
        if( character == board[j][i-1] )
        {
            if (used[j][i-1] != true) {
                location.push_back( j * col + (i-1));
                i--;  //char is found, so adjust coordinates for fn call
                //used.push_back( character ); //add character to vector

                if ( word.length() != 1)
	                flag = findNextChar( j, i, word.substr( 1, word.length()-1), used ); //flag will be set when fn returns
                else
                    return 1;
            }
       }
    }

    //RIGHT NEIGHBOR
    if( i + 1 < this -> col  ){
        cout << "Should go in here" << endl;
       //check if letter at j, i+1 is next letter
        if( character == board[j][i+1] ){
            if (used[j][i+1] != true) {
                cout << "FOUNNND" << endl;
                location.push_back( j * col + (i + 1));
                i++;
 
                if ( word.length() != 1)
	                flag = findNextChar( j, i, word.substr( 1, word.length()-1), used ); //flag will be set when fn returns
                else
                    return 1;
            }
       }
    }

    //TOP LEFT NEIGHBOR
    if( i - 1 >= 0 && j - 1 >= 0 ){
 
       //check if letter at j, i+1 is next letter
        if( character == board[j-1][i-1] ){
            cout << "FOUNNND" << endl;
            if (used[j-1][i-1] != true) {
                location.push_back( (j - 1) * col + (i - 1));
                i--;
                j--;

                if ( word.length() != 1)
	                flag = findNextChar( j, i, word.substr( 1, word.length()-1), used ); //flag will be set when fn returns
                else
                    return 1;
            }
       }
    }

    //TOP RIGHT NEIGHBOR
    if( i + 1 < this -> row && j - 1 >= 0 ){
 
       //check if letter at j, i+1 is next letter
        if( character == board[j-1][i+1] ){

            if (used[j-1][i+1] != true) {
                location.push_back( (j - 1) * col + (i + 1));
                i++;
                j--;

                if ( word.length() != 1)
	                flag = findNextChar( j, i, word.substr( 1, word.length()-1), used ); //flag will be set when fn returns
                else
                    return 1;
            }
       }
    }


    //BOTTOM LEFT NEIGHBOR
    if( i - 1 >= 0 && j + 1 < this -> col ){
       //check if letter at j, i+1 is next letter
        if( character == board[j+1][i-1] ) {
            i--;
            j++;
            if (used[j][i] != true) {
                location.push_back( j * col + i);

                if ( word.length() != 1)
	                flag = findNextChar( j, i, word.substr( 1, word.length()-1), used ); //flag will be set when fn returns
                else
                    return 1;
            }
       }
    }

    //BOTTOM RIGHT NEIGHBOR
    if( i + 1 < this->row && j + 1 < this -> col ){
 
       //check if letter at j, i+1 is next letter
        if( character == board[j+1][i+1] ){
            i++;
            j++;
            if (used[j][i] != true) {
                location.push_back( j * col + i);
            
                if ( word.length() != 1)
	                flag = findNextChar( j, i, word.substr( 1, word.length()-1), used ); //flag will be set when fn returns
                else
                    return 1;
            }
       }
    }

    return flag;
}





vector<int> BogglePlayer::isOnBoard(const string& word_to_check) {
    vector<int> templocation;
    bool **used = new bool*[row];
    for (int i = 0; i < row; i++) {
        used[i] = new bool[col];
        for (int j = 0; j < col; j++) {
            used[i][j] = false;
        }
    }



    // If the param word_to_check is on the board, then return a vector of the positions of letters
    // in proper word order - R * Width + C
    
    // Return empty vector if the word is not on the board or if setBoard() hasn't been called yet

    if(!setCalled)
        return location;
    
    int wordpos = 0;
    int found = 0;
    for (int j = 0; j < row; j++) {
        for (int i = 0; i < col; i++) {
            //check char from board and check first char of word_to_check    
	        std::string str = word_to_check.substr(0, 1); //start at index[0], only take one letter
            //std::cout << "substr " << str << endl;
            //std::cout << "boardji " << board[j][i] << endl;
             if( str == board[j][i] && found != 1){
                 // Found the character, add to locations

                location.push_back( j * col + i);
                if (word_to_check.length() > 1) {
                    used[j][i] = true;
                    found = findNextChar( j, i, word_to_check.substr(1, word_to_check.length() - 1), used );	
                }
             }
        }
    }

    std::cout << "Found? - " << found << endl;

    if (location.size() > 0 && found == 1) {
        cout << "Printing indices: ";
        templocation = location;
        for (int i = 0; i < templocation.size(); i++) {
            cout << templocation[i];
        }
        cout << endl;
    }
    location.clear();
    return templocation;
}



void BogglePlayer::getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols){


}
