#include "baseboggleplayer.h"
#include "boggleplayer.h"
#include <iostream>
#include <vector>
#include <string>
#include <set>

int main (int argc, char* argv[]) {

  BaseBogglePlayer * p = new BogglePlayer();
  set<string> lex;
  

  string wordA("a");
  string wordX("x"); 

  //lex.insert(wordA);
  lex.insert("efgh");


  /*
  string row0[] = {"a","b", "c", "d"};
  string row1[] = {"e","f", "g", "h" };
  string row2[] = {"i", "j", "k", "l"};
  string row3[] = {"m", "n", "o", "p"};
  */

  string row0[] = {"h","g"};
  string row1[] = {"e","f"};

  string* board[] = {row0,row1};
  set<string> words;
  vector<int> locations;

  p->buildLexicon(lex);

  p->setBoard(2,2,board);

  
  if(!p->isInLexicon("efgh")) {
    std::cerr << "Apparent problem with isInLexicon #1." << std::endl;
    return -1;
  }

 /* if(!p->isInLexicon(wordA)) {
    std::cerr << "Apparent problem with isInLexicon #2." << std::endl;
    return -1;
  }
*/
  /*
  if(p->isOnBoard(wordX).size() > 0) {
    std::cerr << "Apparent problem with isOnBoard #1." << std::endl;
    return -1;
  }

  locations.clear();
  locations = p->isOnBoard(wordA);
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
    
    locations.clear();
    locations = p->isOnBoard("abcd");

    for (int i = 0; i < locations.size(); i++) {
            std::cout << locations[i] << std::endl;
    }
    if (locations.size() == 0)
        std::cerr << "Word NOT found" << endl;
    else
        std::cerr << "Word FOUND" << endl;

    std::cerr << "Check indices for #MEGACUSTOM." << std::endl;
    
  
  /*
  if( !p -> getAllValidWords(0,&words)) {
    std::cerr << "Apparent problem with getAllValidWords #1." << std::endl;
    return -1;
  }

  if( words.size() != 1 || words.count(wordA) != 1) {
    std::cerr << "Apparent problem with getAllValidWords #2." << std::endl;
    return -1;
  } */

  if ( !p -> getAllValidWords(0, &words)) {
    std::cout << "Get valid words return no words" << endl;
  }

  if (words.size() != 4) {
    std::cout << "Get valid words does not contain 4. It contains: " << words.size() << endl;
  }
  //std::cout << "Get valid words does not contain 4. It contains: " << words.size() << endl;



  delete p;
  return 0;

}
