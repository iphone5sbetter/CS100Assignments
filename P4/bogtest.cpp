#include "baseboggleplayer.h"
#include "boggleplayer.h"
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include "boggleboard.h"
#include <fstream>
#include <string>

int main (int argc, char* argv[]) {

  BaseBogglePlayer * p = new BogglePlayer();
  set<string> lex;

  /*
  lex.insert("efgh");
    lex.insert("abc");
    lex.insert("cfk");
    lex.insert("lko");
    lex.insert("mno");

  string row0[] = {"a","b", "c", "d"};
  string row1[] = {"e","f", "g", "h" };
  string row2[] = {"i", "j", "k", "l"};
  string row3[] = {"m", "n", "o", "p"}; */

  
  //string* board[] = {row0,row1, row2, row3};
  
  // build the lexicon
  
set<string> words;
  vector<int> locations;

  string** board;
        
    std::ifstream file("lex.txt");
    std::string str; 
    while (std::getline(file, str))
    {
        // add str to lexicon
        std::cout << "str - " << str << endl;
        lex.insert(str);
    }

    int row = 20;
    int col = 23;

    // build the board
     std::ifstream brd("brd.txt");
    getline(brd, str);
    getline(brd, str);

    board = new string*[row]; // rows
    for (int r = 0; r < row; r++) {
        board[r] = new string[col]; //cols
        for (int c = 0; c < col; c++) {
            getline(brd, str);
            std::cout << "str - " << str << endl;
            board[r][c] = str;
        }
    }


  

  p->buildLexicon(lex);

  p->setBoard(row,col,board);

  /*
  if(!p->isInLexicon("efgh")) {
    std::cerr << "Apparent problem with isInLexicon #1." << std::endl;
    //return -1;
  } 
  */

 /* if(!p->isInLexicon(wordA)) {
    std::cerr << "Apparent problem with isInLexicon #2." << std::endl;
    return -1;
  }
*/
  /*
  if(!p->isOnBoard("afkon").size() > 0) {
    std::cerr << "Apparent problem with isOnBoard #1." << std::endl;
    //return -1;
  }
  */

  locations.clear();
  /*
  locations = p->isOnBoard();
  if(locations.size() != 1 || locations[0] != 3) {
    std::cerr << "Apparent problem with isOnBoard #2." << std::endl;
    return -1;
  } */

  /*
  // CUSTOM
    locations.clear();
    locations = p->isOnBoard("dc");
    if(locations.size() != 2 || locations[0] != 0 || locations[1] != 1) {
        std::cerr << "Apparent problem with isOnBoard #CUSTOM." << std::endl;
        return -1;
    }*/

    // Hard CUSTOM
    
  /*
    locations.clear();
    locations = p->isOnBoard("abcd");

    for (int i = 0; i < locations.size(); i++) {
            std::cout << locations[i] << std::endl;
    }
    if (locations.size() == 0)
        std::cerr << "Word NOT found" << endl;
    else
        std::cerr << "Word FOUND" << endl;

    std::cerr << "Check indices for #MEGACUSTOM." << std::endl; */
    
  
  /*
  if( !p -> getAllValidWords(0,&words)) {
    std::cerr << "Apparent problem with getAllValidWords #1." << std::endl;
    return -1;
  }

  if( words.size() != 1 || words.count(wordA) != 1) {
    std::cerr << "Apparent problem with getAllValidWords #2." << std::endl;
    return -1;
  } */

  if ( !p -> getAllValidWords(2, &words)) {
    std::cout << "Get valid words return no words" << endl;
  }

  std::cout << "Get valid words contains: " << words.size() << endl;
  
  //std::cout << "Get valid words does not contain 4. It contains: " << words.size() << endl;


  delete p;
  return 0;

}
