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


void alphaTrie:: insert(const string &word){
  if( root == nullptr){
   alphaNode* node = new alphaNode<char>();
   this -> root = node;  //set root = current node
  }

 alphaNode* current = this -> root;

//TODO
}

void alphaTrie:: find(const string &word){


}
