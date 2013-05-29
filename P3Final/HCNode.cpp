// Daniel Brim <dbrim@ucsd.edu>, Tyler Pollak <cs100tak@ieng6.edu>
#include "HCNode.hpp"

/** Less-than comparison, so HCNodes will work in std::priority_queue
  *  We want small counts to have high priority.
  *  And we want to break ties deterministically. Defining operator.
  */
bool HCNode:: operator<(const HCNode& other){
  
    if (this -> count != other.count)
        return this->count > other.count;
    return this->symbol < other.symbol;
}


/* Function to do comparisons using the < operator
 *
 */ 
bool HCNode::comp(HCNode* one, HCNode* other){
    return *one < *other;
}

HCNode::~HCNode(){ 
    if (c0)
        delete c0;
    if (c1)
        delete c1;
}
