// Daniel Brim <dbrim@ucsd.edu>, Tyler Pollak <cs100tak@ieng6.edu>
#include "boggleutil.h"

/* Helper method for destructor */
void alphaTrie:: makeEmpty(alphaNode* &curr){

  for(int i = 0; i < 26; i++){
    if(curr -> child[i] != nullptr){
      makeEmpty(curr -> child[i]);   //delete current node recursively
    }
   }
  delete curr;
  curr = nullptr;  //no hanging pointers
}

/* DESTRUCTOR */
alphaTrie::~alphaTrie(){
   makeEmpty(root);
} 

// Insert word into alphaTrie
void alphaTrie:: insert(const string &word){
    if( root == nullptr){
        alphaNode* node = new alphaNode();
        this -> root = node;  //set root = current node
    }
    alphaNode* current = this -> root;
    
    // For every letter in the word
    for (unsigned int i = 0; i < word.length(); i++) {
        int pos = word[i] - 97; // Convert the letter into a position
        // Check to see if there's a node already there
        if ( current -> child[pos] == nullptr ) {
            alphaNode* newnode = new alphaNode(); // Create a child node
            current -> child[pos] = newnode; // Save the child node ptr
            current = newnode; // Become the new node!
        }
        else {
            current = current -> child[pos]; //Follow tree down
        }

        // Set the flag if it's the last character in the word
        if (i == word.length()-1)
            current -> flag = true;
    }
}

//Find function for alphaTrie. Returns true if found, false otherwise.
bool alphaTrie:: find(const string &word){
    if (root == nullptr) {
        return false;
    }

    alphaNode *current = this -> root;

    for (unsigned int i = 0; i < word.length(); i++) {
        //Reset indexes of letters in alphabet
        int pos = word[i] - 97;
        // Chec to see if there's a node there
        if (current -> child[pos] == nullptr) {
            return false;
        }
        else {
            current = current -> child[pos];
        }

        if (i == word.length() - 1){
            return current -> flag;
           }
    }
    return false;
}
