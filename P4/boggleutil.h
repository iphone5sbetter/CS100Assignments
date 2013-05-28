#ifndef BOGGLEUTIL_H
#define BOGGLEUTIL_H 


/* Node class for alphaTrie */
class alphaNode{ 

public:

  char letter; //will be set to letter of word later
  // child of each alphaNode* is an alphaNode*
  alphaNode* child[26];
  bool flag;

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

 void makeEmpty(alphaNode* &curr){}
 
protected:
 /* Create alphaNode* root and size */
 alphaNode* root;
 unsigned int size;



public:
/* root = nullptr; size = 0; */
 alphaTrie() : root(nullptr), size(0) {}

 /* Destructor */
 virtual ~alphaTrie(){} 


 void insert(const string &word);
 bool find(const string &word);
};




#endif // BOGGLEUTIL_HPP
