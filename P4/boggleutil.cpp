#include "boggleutil.h"

alphaTrie:: alphaTrie(){

/* Helper method for destructor */
void boggleutil:: makeEmpty(alphaNode* &curr){

 alphaNode* node;
 alphaNode* deleteNode;

  for(int i = 0; i < 26; i++){
    if(curr -> child[i] != nullptr){
      makeEmpty(curr -> child[i]);   //delete current node recursively
    }
   }
  delete curr;
  curr = nullptr;  //no hanging pointers
}

/* DESTRUCTOR */
 virtual ~alphaTrie(){
   makeEmpty(root);
 } 

};

// this may not work for upper case - may need to force lowercase somewhere
void alphaTrie:: insert(const string &word){
    if( root == nullptr){
        alphaNode* node = new alphaNode<char>();
        this -> root = node;  //set root = current node
    }
    alphaNode* current = this -> root;
    
    // For every letter in the word
    for (int i = 0; i < word.length(); i++) {
        int pos = word[i] - 97; // Convert the letter into a position
        
        // Check to see if there's a node already there
        if ( child[pos] == nullptr ) {
            alphaNode* newnode = new alphaNode<char>(); // Create a child node
            current -> child[pos] = newnode; // Save the child node ptr
            current = newnode; // Become the new node!
        }
        else {
            current = child[pos];
        }

        // Set the flag if it's the last character in the word
        if (i == word.length()-1)
            current -> flag = true;
    }
}

bool alphaTrie:: find(const string &word){

}
