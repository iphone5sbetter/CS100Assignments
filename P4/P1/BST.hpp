/*
 * cs100s   P1   April 11, 2013
 *
 * Daniel Brim - dbrim - A09828025
 * Tyler Pollak - cs100tak - A09965467
 *
 * Partner submission - one joint turnin
 */


#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <utility> // for std::pair

template<typename Data>
class BST {

protected:

  /** Pointer to the root of this BST, or nullptr if the BST is empty */
  BSTNode<Data>* root;

  /** Number of Data items stored in this BST. */
  unsigned int isize;

private:	
  /** Return a pointer to the node containing the smallest data	* item in the BST subtree rooted at n,
  * or nullptr if n is nullptr
  */
  static BSTNode<Data>* first(BSTNode<Data>* n) {
	if (n == nullptr)
        return nullptr;
    if(n->left == nullptr)
        return n;
    return first(n->left); // Recursively find lowest left node.
      
  }
  
  /**
   * Helper function.
   * Empties a BST by nullifying the pointers
   * and deleting the memory.
   */
  void makeEmpty(BSTNode<Data>* & t) {
    if (t != nullptr) {
      makeEmpty(t->left);
      makeEmpty(t->right);
      delete t; // Delete memory
    }
    t = nullptr;
  }


public:

  /** iterator is an aliased typename for BSTIterator<Data>. */
  typedef BSTIterator<Data> iterator;

  /** Default constructor.
      Initialize an empty BST.
   */
  BST() : root(nullptr), isize(0)  {
  }


  /** Default destructor.
   *  It is virtual, to allow appropriate destruction of subclass objects.
   *  Delete every node in this BST.
   */ // TODO
  virtual ~BST() {
    makeEmpty(root);
  }

  /** Insert a Data item in the BST.
   *  Return a pair, with the pair's first member set to an
   *  iterator pointing to either the newly inserted element
   *  or to the equivalent element already in the set.
   *  The pair's second element is set to true
   *  if a new element was inserted or false if an
   *  equivalent element already existed.
   */ // TODO
  virtual std::pair<iterator,bool> insert(const Data& item) {
    // If there's no root, just insert new node as root
    if(root == nullptr) {
      BSTNode<Data> *newnode = new BSTNode<Data>(item);
      root = newnode;
      iterator itr(root);
      std::pair<iterator,bool> p = make_pair(itr,true);
      isize++;
      return p;
    }
    
    else {
      BSTNode<Data> *newnode = root;	
   	  while (newnode != nullptr)
	  {
	    if(newnode->data == item) {
            // We found a duplicate, return false.
          iterator itr(newnode);
          std::pair<iterator,bool> p = make_pair(itr,false);
          return p;
       	}
        
        else if(newnode->data > item) {
            //insert my new node in to the left subtree of the root
		    if (newnode->left != nullptr)
			    newnode = newnode->left; //loop to left	
		    else {
		        // At the end, add the node.
			    newnode->left = new BSTNode<Data>(item);
                newnode->left->parent = newnode;
			    iterator itr(newnode->left);
			    std::pair<iterator,bool> p = make_pair(itr,true);
                isize++;
			    return p;
	        }
        }
        else if(newnode->data < item) {
          //insert my new node in to the right subtree of the root
          if (newnode->right != nullptr) {
		    newnode = newnode->right; // Keep looking
		  }
		  else {
		    // At the end, add the node.
		    newnode->right = new BSTNode<Data>(item);
            newnode->right->parent = newnode;    
		    iterator itr(newnode->right);
	        std::pair<iterator,bool> p = make_pair(itr,true);
            isize++;
	        return p;
		  }
        }
        
	  } 
	}
    
    iterator itr(nullptr);
    std::pair<iterator,bool> p = make_pair(itr,false);
    return p;
    
  }



    /** Find a Data item in the BST.
     *  Return an iterator pointing to the item, or the end
     *  iterator if the item is not in the BST.
     */ // TODO
    iterator find(const Data& item) const {
        
        if(root == nullptr) {
            return end();   // Nothing in BST. Can't find.                       
        }
        else {
            BSTNode<Data> *newnode = root;	
            while (newnode != nullptr)
            {
                if(newnode->data == item) {
	                // Found item, return iterator
                    iterator itr(newnode);
                    return itr;
       	        }
                else if(newnode->data > item) {
                    // Item is less; need to look down left subtree
		            newnode = newnode->left; //loop to left	
                }
                else if(newnode->data < item) {
                    //insert my new node in to the right subtree of the root
 		            newnode = newnode->right;
	            }
            }
            // Didn't find item, so we exit loop and return null iterator
            return end();
        }
        return end();
    }

  
  /** Return the number of items currently in the BST.
   */ // TODO
  unsigned int size() const {
	return isize;
  }

  /** Remove all elements from this BST, and destroy them,
   *  leaving this BST with a size of 0.
   */ // TODO
  void clear() {
    // Calls the helper function to delete the BST.
    makeEmpty(root);
    isize = 0; // Reset size
  }

  /** Return true if the BST is empty, else false.
   */ // TODO
  bool empty() const {
	if (root != nullptr)
		return false;
	else // Root has something, so BST not empty
		return true;
  }

  /** Return an iterator pointing to the first item in the BST.
   */ // TODO
  iterator begin() const {
	return BSTIterator<Data>( first(root) ); // returns the first node
  }

  /** Return an iterator pointing past the last item in the BST.
   */
  iterator end() const {
    return typename BST<Data>::iterator(nullptr);
  }

 };


#endif //BST_HPP
