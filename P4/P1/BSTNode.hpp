/*
 * cs100s   P1   April 11, 2013
 *
 * Daniel Brim - dbrim - A09828025
 * Tyler Pollak - cs100tak - A09965467
 *
 * Partner submission - one joint turnin
 */

#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iostream>
#include <iomanip>

using namespace std;

/** This class template defines a node type for the BST container.
 *  Note that all members are public. So, the BST implementation should
 *  take care not to expose any BSTNode objects.
 */
template<typename Data>
class BSTNode {

public:

  /** Member variables. */
  BSTNode<Data>* parent;
  BSTNode<Data>* left;
  BSTNode<Data>* right;
  const Data data;  // the const Data in this node
  int info;  // variable used in advanced algorithms 

  /** Constructor.  Initialize a BSTNode with the given Data item,
   *  no parent, and no children.
   */
  BSTNode(const Data & d): data(d) {
    left = right = parent = nullptr;
  }


  /** Return the inorder successor of this BSTNode in a BST,
   *  or nullptr if none.
   *  PRECONDITION: this BSTNode is a node in a BST.
   *  POSTCONDITION:  the BST is unchanged.
   *  RETURNS: the BSTNode that is the inorder successor of this BSTNode,
   *  or nullptr if there is none.
   */ // TODO
  BSTNode<Data>* successor() {
      
	if (this->right != nullptr) // If there's a right child
	{
        BSTNode<Data>* temp = this->right;
        if (temp->left != nullptr)
        {
            // Find lowest left child
            while (temp->left != nullptr)
            {
                temp = temp->left;
            }
            return temp;
        }
        else {
            return temp;
        }
    }
	else //if (this->parent != nullptr) // There's only a left child
    {
        BSTNode<Data>* node = this;
        BSTNode<Data> *p = node->parent;
        // Go until we find a node with no parent
        while( p != nullptr && node == p->right)
        {
            node = p;
            p = p->parent;
        }
        return p; // Return the parentless node
    }
    return nullptr; 
  }
}; 

/** Overload operator<< to insert a BSTNode's fields in an ostream. */
template <typename Data>
std::ostream & operator<<(std::ostream& stm, const BSTNode<Data> & n) {
  stm << '[';
  stm << std::setw(10) << &n;                 // address of the BSTNode
  stm << "; p:" << std::setw(10) << n.parent; // address of its parent
  stm << "; l:" << std::setw(10) << n.left;   // address of its left child
  stm << "; r:" << std::setw(10) << n.right;  // address of its right child
  stm << "; i:" << std::setw(10) << n.info;   // its info field
  stm << "; d:" << n.data;                    // its data field
  stm << ']';
  return stm;
}

#endif // BSTNODE_HPP
