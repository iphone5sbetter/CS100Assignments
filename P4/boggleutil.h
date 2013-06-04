// Daniel Brim <dbrim@ucsd.edu>, Tyler Pollak <cs100tak@ieng6.edu>
#ifndef BOGGLEUTIL_H
#define BOGGLEUTIL_H 

#include <iostream>
#include <string>

using namespace std;

/* Node class for alphaTrie */
class alphaNode{ 

public:

  char letter; 
  // child of each alphaNode* is an alphaNode*
  alphaNode* child[26];
  bool flag;
  bool trimmed;

/* Node class for alphaNode */
 alphaNode(){
    this -> letter = '\0';  
    for(int i = 0; i < 26; i++){
     child[i] = nullptr;   //creates an array of 26 alphaNode pointers
    }
    flag = false;
 }
 
};


class alphaTrie {
  
private:

//Helper function for destructor
 void makeEmpty(alphaNode* &curr);


public:

    /* Create alphaNode* root and size */
    alphaNode* root;
    unsigned int size;

    /* root = nullptr; size = 0; */
    alphaTrie() : root(nullptr), size(0) {}

    /* Destructor */
    ~alphaTrie();


    void insert(const string &word);
    bool find(const string &word);
};

#endif // BOGGLEUTIL_HPP
