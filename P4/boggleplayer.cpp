// Daniel Brim <dbrim@ucsd.edu>, Tyler Pollak <cs100tak@ieng6.edu>
#include "boggleplayer.h"
#include <queue>
/*
 * Takes as argument a set containing words specifying the official
 * lexicon to be used. Each word in the set will be a string consisting
 * of lowercase a-z only. Function must load the words into an efficient
 * datastructure that will be used internally as needed by the BogglePlayer
 */
std::set<string> lexicon_words;

static std::string toLowerCase(std::string strToConvert){
  std::string res;
  for (std::string::iterator p = strToConvert.begin();
                                 strToConvert.end() != p; ++p)
    res += tolower(*p);
  return res;
}

void BogglePlayer::buildLexicon(const std::set<string>& word_list){
  set<string>:: const_iterator it = word_list.begin();
  set<string>:: const_iterator end = word_list.end();
  this -> t = new alphaTrie();

  while(it != end){
      t -> insert(toLowerCase(*it));//insert into t using alphaTrie's insert

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
    board[r] = new string[cols];
	for(unsigned int c = 0; c < cols; c++){
	 this->board[r][c] = toLowerCase(diceArray[r][c]);
	}
  }

   setCalled = true;
}

void BogglePlayer::findMoreWords(int r, int c, string word, bool** visited, 
        set<string>* words, alphaNode *node, unsigned int length ) {
    visited[r][c] = true;

    // get char on the board
    string str = board[r][c];

    // add it to the growing word
    word.append(str); 
    
    // get the char as an actual char
    char ch = str[0];
    int pos = ch - 97;

// check if the character is in the board's array
    
    if (node->child[pos] != NULL)
    {
        if (node->child[pos] -> flag == true && word.length() >= length ) {
            words -> insert(word);
        }

// if the next indices are on the board and not in isvisited, recurse

//top
if (r-1 >= 0)
  if (!visited[r-1][c]) 
    findMoreWords(r-1, c, word, visited, words, node->child[pos], length);
           
//left
if (c-1 >= 0) 
  if (!visited[r][c-1]) 
    findMoreWords(r, c-1, word, visited, words,node->child[pos], length);
            
//bottom
if (r+1 < row) 
 if (!visited[r+1][c]) 
  findMoreWords(r+1, c, word, visited, words,node->child[pos], length);

//right           
if (c+1 < col) 
  if (!visited[r][c+1]) 
    findMoreWords(r, c+1, word, visited, words,node->child[pos], length);
            
// top left
if (r-1 >= 0 && c-1 >=0) 
  if (!visited[r-1][c-1]) 
    findMoreWords(r-1, c-1, word, visited, words,node->child[pos], length);
            
// top right
  if (r-1 >= 0 && c+1 < col)
    if (!visited[r-1][c+1]) 
      findMoreWords(r-1, c+1, word, visited, words,node->child[pos], length);
            
// bottom left
  if (r+1 < row && c-1 >=0)
    if( !visited[r+1][c-1]) {
      findMoreWords(r+1, c-1, word, visited, words,node->child[pos], length);
    }
        
// bottom right
if (r+1 < row && c+1 < col)
  if (!visited[r+1][c+1]) 
    findMoreWords(r+1, c+1, word, visited, words,node->child[pos], length);
        
    visited[r][c] = false;
} 
    
else {
        visited[r][c] = false;
}
        return; 
        
}

/*
 * Takes an int specifying min word length, and a pointer to a set of strings.
 * Returns false if setBoard() or buildLexicon() have not been called for this
 * BogglePlayer. If they have, it will return true after: 
 *  1)Filling the set with words that are at least the given min length
 *  2) Are in lexicon specified by the most recent call to buildLexicon()
 *  3) Can be found following an acyclic simple path on the board 
 *     specified by the most recent call to setBoard()
 */
bool BogglePlayer::getAllValidWords(unsigned int minimum_word_length, 
        set<string>* words ){
    // Return false if buildLexicon() or setBoard() hasn't been build yet
    if (buildCalled == false || setCalled == false)
        return false;

    // 2-D array of bools for used
    bool **used = new bool*[row];
    for (int i = 0; i < row; i++) {
        used[i] = new bool[col];
        for (int j = 0; j < col; j++) {
            used[i][j] = false;
        }
    }

    for (int r = 0; r < row; r++)
        for (int c = 0; c < col; c++) {
            BogglePlayer::findMoreWords( r, c, "", used, words, t->root,
                                         minimum_word_length);
        }

    return true; 
}

// isInLexicon checks if word_to_check is a valid string in
// the alphabet trie
bool BogglePlayer::isInLexicon(const string& word_to_check){

    if (t -> root == nullptr) {
        return false;
    }
    if (t -> find(word_to_check)) {
        return true;
    }
   
    return false;      
}


// Returns 1 if complete word is found, returns 0 if word not found
// Fills  2-D array of booleans to hold flags if word was found at index
int BogglePlayer:: findNextChar( int j, int i, string word, bool **used){
     int flag = 0; 
     std::string character = word.substr(0, 1);  //take next character

     used[j][i] = true;

  //TOP NEIGHBOR
  if( j - 1 >= 0 && flag != 1 ){
    //check if letter at j-1, i is next letter
    if( character == board[j-1][i] ){
     j--; //update coordinate for fn call
     if (used[j][i] != true) {
       location.push_back( j * col + i ); //push location into vector
        if ( word.length() != 1 ) 
             //flag will be set when function returns
	     flag = findNextChar( j, i, word.substr(1,word.length()-1), used);
        else 
           flag = 1;
    }
    j++; //reset character for next check
  }
} 

  //BOTTOM NEIGHBOR
    if( j + 1 < this -> row && flag !=1 ){
    //check if letter at j+1,i is next letter
     if( character == board[j+1][i] ){
       j++; //update coordinate for fn call
       if (used[j][i] != true) {
         location.push_back( j * col + i);
         if ( word.length() != 1) 
	     flag = findNextChar( j, i, word.substr(1,word.length()-1), used); 
              //flag will be set when function returns
         else 
           flag = 1;  
        }
        j--;  //reset character for next check
    }
}

    //LEFT NEIGHBOR
    if( i - 1 >= 0 && flag != 1){
       //check if letter at j,i-1 is next letter
      if( character == board[j][i-1] ){
          i--; //update coordinate for fn call
          if (used[j][i] != true) {
              location.push_back( j * col + i);
              if ( word.length() != 1)
                 //flag will be set when fn returns 
                 flag = findNextChar(j,i,word.substr(1,word.length()-1),used); 
              else
                  flag = 1;
          }
          i++;  //reset character for next check
     }
  }

    //RIGHT NEIGHBOR
    if( i + 1 < this -> col && flag != 1 ){
       //check if letter at j, i+1 is next letter
        if( character == board[j][i+1] ){
            i++; //update coordinate for fn call
            if (used[j][i] != true) {
                location.push_back( j * col + i);
                if ( word.length() != 1)
                  //flag will be set when fn returns
	          flag = findNextChar(j,i,word.substr(1,word.length()-1),used);  
                else
                    flag = 1;
            }
            i--; //reset character for next check
       }
    }

    //TOP LEFT NEIGHBOR
    if( i - 1 >= 0 && j - 1 >= 0 && flag !=1 ){
       //check if letter at j, i+1 is next letter
        if( character == board[j-1][i-1] ){
            i--; //update for fn call
            j--;
            if (used[j][i] != true) {
                location.push_back( j * col + i);
                if ( word.length() != 1)
                  //flag will be set when fn returns
	          flag=findNextChar(j,i,word.substr(1,word.length()-1),used);
                else
                  flag = 1;
            }
            i++; //reset character for next check
            j++;
       }
    }

    //TOP RIGHT NEIGHBOR
    if( i + 1 < this -> row && j - 1 >= 0 && flag != 1 ){
       //check if letter at j, i+1 is next letter
        if( character == board[j-1][i+1] ){
            j--; //update for fn call
            i++;
            if (used[j][i] != true) {
                location.push_back( j * col + i );
                if ( word.length() != 1)
	           flag =findNextChar(j,i,word.substr(1,word.length()-1),used);
                else
                    flag = 1;
            }
            j++; //reset character for next check
            i--;
       }
    }


    //BOTTOM LEFT NEIGHBOR
    if( i - 1 >= 0 && j + 1 < this -> col && flag != 1 ){
       //check if letter at j, i+1 is next letter
        if( character == board[j+1][i-1] ) {
            i--;  //update for fn call
            j++;
            if (used[j][i] != true) {
                location.push_back( j * col + i);
                if ( word.length() != 1)
	          flag= findNextChar(j,i,word.substr(1,word.length()-1),used);
                else
                    flag = 1;
            }
            i++; //reset character for next check
            j--;
       }
    }


    //BOTTOM RIGHT NEIGHBOR
    if( i + 1 < this->row && j + 1 < this -> col && flag != 1 ){
       //check if letter at j, i+1 is next letter
        if( character == board[j+1][i+1] ){
            i++; //update for fn call
            j++;
            if (used[j][i] != true) {
                location.push_back( j * col + i );
              if ( word.length() != 1)
	        flag=  findNextChar(j,i,word.substr(1,word.length()-1),used); 
              else
                flag = 1;
            }
            i--;
            j--; //reset character for next check
       }
    }

    used[j][i] = false;

    if (flag == 0)
        location.pop_back();

    return flag;
}

// If the param word_to_check is on the board, 
// then return a vector of the positions of letters
// in proper word order - R * Width + C    
// Return empty vector if the word is not on the board or 
// if setBoard() hasn't been called yet
vector<int> BogglePlayer::isOnBoard(const string& word_to_check) {
    
    if(!setCalled || !buildCalled)
        return location;
    //force words to lowerCase
    string news = toLowerCase(word_to_check);
    vector<int> templocation;
    //create 2-D bool array
    bool **used = new bool*[row];
    for (int i = 0; i < row; i++) {
        used[i] = new bool[col];
        for (int j = 0; j < col; j++) {
            used[i][j] = false;
        }
    }
        
    int found = 0;
    for (int j = 0; j < row; j++) {
        for (int i = 0; i < col; i++){
            //check char from board and check first char of word_to_check    
	        std::string str = word_to_check.substr(0, 1); 
            //start at index[0], only take one letter
             if( str == board[j][i] && found != 1){
              location.clear();
                 // Found the character, add to locations
              location.push_back( j * col + i);
              if (word_to_check.length() > 1) {
                used[j][i] = true;
                //call helper function to trace path of rest of word
                found= findNextChar( j, i,
                      word_to_check.substr(1,word_to_check.length()-1),used);	
                used[j][i] = false;
                }
             }
        }
    }

    if (location.size() > 0 && found == 1) {
        templocation = location;
    }
    location.clear(); //clear locations vector
    return templocation;
}


// Creates a custom board specified by the user
void BogglePlayer::getCustomBoard(string** &new_board,
                                  unsigned int *rows, unsigned int *cols){
    setBoard(*rows, *cols, new_board);
}

