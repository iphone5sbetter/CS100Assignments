#include "boggleplayer.h"
#include <queue>
/*
 * Takes as argument a set containing words specifying the official lexicon to be used. 
 * Each word in the set will be a string consisting of lowercase a-z only. Function must
 * load the words into an efficient datastructure that will be used internally as needed
 * by the BogglePlayer
 */


static std::string toLowerCase(std::string strToConvert){
  std::string res;
  for (std::string::iterator p = strToConvert.begin(); strToConvert.end() != p; ++p)
    res += tolower(*p);
  return res;
}

void BogglePlayer::buildLexicon(const std::set<string>& word_list){
  set<string>:: const_iterator it = word_list.begin();
  set<string>:: const_iterator end = word_list.end();
  this -> t = new alphaTrie();

  while(it != end){
      t -> insert(toLowerCase(*it));   //insert into t using alphaTrie's insert

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
	 this->board[r][c] = toLowerCase(diceArray[r][c]);
     std::cout << "Board: " << diceArray[r][c] << endl;
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
bool BogglePlayer::getAllValidWords(unsigned int minimum_word_length, set<string>* words ){

    // Return false if buildLexicon() or setBoard() hasn't been build yet
    if (buildCalled == false || setCalled == false)
        return false;

    bool **used = new bool*[row];
    for (int i = 0; i < row; i++) {
        used[i] = new bool[col];
        for (int j = 0; j < col; j++) {
            used[i][j] = false;
        }
    }




    // speed will change depending on if you call isInLexicon or isOnBoard first

    // To get all words on board...
    // Make a queue of all non-check spaces on the board
    // Dequeue the first one, queue up all spaces that haven't been checked yet
    
    //BogglePlayer::dealWithTrie( t -> root, "", 0, minimum_word_length, words, used );
    return true; 
}

bool BogglePlayer::isInLexicon(const string& word_to_check){

    if (t -> root == nullptr) {
        return false;
    }
    if (t -> find(word_to_check)) {
        return true;
    }
   
    return false;      
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
        if( character == board[j-1][i] ){
            j--; //update coordinate
            if (used[j][i] != true) {
                location.push_back( j * col + i ); //push location into vector
                if ( word.length() != 1 ) 
	                flag = findNextChar( j, i, word.substr( 1, word.length()-1), used ); //flag will be set when function returns
                else 
                    flag = 1;
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
                if ( word.length() != 1) 
	                flag = findNextChar( j, i, word.substr( 1, word.length()-1), used ); //flag will be set when function returns
                else 
                    flag = 1;  
            }
        }
    }

    //LEFT NEIGHBOR
    if( i - 1 >= 0 ){
       //check if letter at j,i-1 is next letter
        if( character == board[j][i-1] ){
            i--;
            if (used[j][i] != true) {
                location.push_back( j * col + i);
                if ( word.length() != 1)
	                flag = findNextChar( j, i, word.substr( 1, word.length()-1), used ); //flag will be set when fn returns
                else
                    flag = 1;
            }
       }
    }

    //RIGHT NEIGHBOR
    if( i + 1 < this -> col  ){
       //check if letter at j, i+1 is next letter
        if( character == board[j][i+1] ){
            i++;
            if (used[j][i] != true) {
                location.push_back( j * col + i);
                if ( word.length() != 1)
	                flag = findNextChar( j, i, word.substr( 1, word.length()-1), used ); //flag will be set when fn returns
                else
                    flag = 1;
            }
       }
    }

    //TOP LEFT NEIGHBOR
    if( i - 1 >= 0 && j - 1 >= 0 ){
       //check if letter at j, i+1 is next letter
        if( character == board[j-1][i-1] ){
            i--;
            j--;
            if (used[j][i] != true) {
                location.push_back( j * col + i);
                if ( word.length() != 1)
	                flag = findNextChar( j, i, word.substr( 1, word.length()-1), used ); //flag will be set when fn returns
                else
                    flag = 1;
            }
       }
    }

    //TOP RIGHT NEIGHBOR
    if( i + 1 < this -> row && j - 1 >= 0 ){
       //check if letter at j, i+1 is next letter
        if( character == board[j-1][i+1] ){
            j--;
            i++;
            if (used[j][i] != true) {
                location.push_back( j * col + i );
                if ( word.length() != 1)
	                flag = findNextChar( j, i, word.substr( 1, word.length()-1), used ); //flag will be set when fn returns
                else
                    flag = 1;
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
                    flag = 1;
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
                location.push_back( j * col + i );
            
                if ( word.length() != 1)
	                flag = findNextChar( j, i, word.substr( 1, word.length()-1), used ); //flag will be set when fn returns
                else
                    flag = 1;
            }
       }
    }

    return flag;
}



vector<int> BogglePlayer::isOnBoard(const string& word_to_check) {
    
    if(!setCalled)
        return location;

    string news = toLowerCase(word_to_check);
    std::cout << "LOOKIN FOR: " << news << endl;
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

        
    int wordpos = 0;
    int found = 0;
    for (int j = 0; j < row; j++) {
        for (int i = 0; i < col; i++){
            //check char from board and check first char of word_to_check    
	        std::string str = word_to_check.substr(0, 1); //start at index[0], only take one letter
             if( str == board[j][i] && found != 1){
                 location.clear();
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
    std:: cout << "templocation.size(): " << templocation.size() << std::endl;
    return templocation;
}



void BogglePlayer::getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols){


}



///////////////////////// BogglePiece methods ////////////////////

void BogglePiece::addAdjacentPiece(BogglePiece piecePtr) {
    this -> adjacentPieces.push_back(piecePtr);
}

vector<BogglePiece> BogglePiece::getAdjacentPieces() {
    return this->adjacentPieces;
}
