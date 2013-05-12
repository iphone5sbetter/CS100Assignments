#include "HCNode.hpp"



/** Less-than comparison, so HCNodes will work in std::priority_queue
  *  We want small counts to have high priority.
  *  And we want to break ties deterministically. Defining operator.
  */
bool HCNode:: operator<(const HCNode& other){
    if(this -> count < other.count){
	    return false;
    }

    //if count of this == count of other, compares symbols to determine priority
    else if(this-> count == other.count)
    {
        if(this-> symbol < other.symbol)
        {
	        return true;
        }

        else
        {
	        return false;
        }
    }

    // if this-> is greater than other-> count
    else
    {
        return true;
    } 

}


/* Function to do comparisons using the < operator
 *
 */ 
bool HCNode::comp(HCNode* one, HCNode* other){
    if(one->count < other->count) 
	    return false;
 
    else if(one->count == other->count)
    {
        if(one->symbol < other->symbol) 
        {
            return true;
        }
        else
  	        return true;
    }
    
    return true;
  }



