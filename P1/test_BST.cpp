#include "BST.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#define MAX 10000

using namespace std;


/**
 * A simple test driver for the BST class template.
 * P1 CSE 100 2013
 * Author: P. Kube (c) 2013
 */
int main() {

  /* Create an STL vector of some ints */
  vector<int> v;
  vector<int> random;
  
    v.push_back(50);
    v.push_back(60);
    v.push_back(30);
    v.push_back(33);
    v.push_back(38);
    v.push_back(35);
    v.push_back(37);
    v.push_back(20);
   // v.push_back(15);
    
  // Overriding for more extensive tests */

 /* 
  srand(time(NULL));
  
  for (int i = 0; i < 10000; i++ )
  {
      int r = rand() % 10000;
      bool dupe = false;

      vector<int>::iterator ranit = random.begin();
      vector<int>::iterator ranen = random.end();
      for(; ranit != ranen; ++ranit) 
      {
        if (*ranit == r) 
        {
          //cout << "dupe" << endl;
          dupe = true;
          // return -1;
        }
      }
      if (!dupe)
      {
          cout << r << endl;
            random.push_back(r);
            v.push_back(r);
      }
  } 
  */

  /* Create an instance of BST holding int */
  BST<int> b;

  /* Insert a few data items. */
  vector<int>::iterator vit = v.begin();
  vector<int>::iterator ven = v.end();
  for(; vit != ven; ++vit) {
    // all these inserts are unique, so should return a std::pair
    // with second part true
    std::pair<BST<int>::iterator,bool> pr = b.insert(*vit);
    if(! pr.second ) {
      cout << "Incorrect bool return value when inserting " << *vit << endl;
      return -1;
    }
    if(*(pr.first) != *vit) {
      cout << "Incorrect iterator return value when inserting " << *vit << endl;
      return -1;
    }  
  }

  /* Test inserting repeated values - expected false result */
  
  /*
  vector<int> z;
  z.push_back(1);
  z.push_back(3);

  vector<int>::iterator bit = z.begin();
  vector<int>::iterator ben = z.end();
  for(; bit !=ben; ++bit) {
      std::pair<BST<int>::iterator,bool> pr = b.insert(*bit);
      if( pr.second ) {
        cout << "Incorrect bool return value when inserting " << *bit << endl;
        return -1;
      }
      if(*(pr.first) != *bit) {
      cout << "Incorrect iterator return value when inserting " << *bit << endl;
      return -1;
    }
  }
  // Make sure size hasn't changed for failed inputs.
  cout << "Size is: " << b.size() << endl;
  if(b.size() == z.size()) {
    cout << "... which is incorrect." << endl;
    return -1;
  }
 */

  /* Test size. */
  cout << "Size is: " << b.size() << endl;
  if(b.size() != v.size()) {
    cout << "... which is incorrect." << endl;
    return -1;
  }

  /* Test find return value. */
  vit = v.begin();
  for(; vit != ven; ++vit) {
    if(*(b.find(*vit)) != *vit) {
      cout << "Incorrect return value when finding " << *vit << endl;
      return -1;
    }
  }
  
  /* Sort the vector, to compare with inorder iteration on the BST */
  sort(v.begin(),v.end());

  /* Test BST iterator; should iterate inorder */
  cout << "traversal using iterator:" << endl;
  vit = v.begin();
  BST<int>::iterator en = b.end();
  BST<int>::iterator it = b.begin();
  for(; vit != ven; ++vit) {
    if(! (it != en) ) {
      cout << *it << "," << *vit << ": Early termination of BST iteration." << endl;
      return -1;
    }
    cout << *it << endl;
    if(*it != *vit) {
      cout << *it << "," << *vit << ": Incorrect inorder iteration of BST." << endl;
      return -1;
    }
    ++it;
  }
  cout << "OK." << endl;

}

