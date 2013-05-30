// Daniel Brim <dbrim@ucsd.edu>, Tyler Pollak <cs100tak@ieng6.edu>
#include "HCTree.hpp"
#include <stack>

/**
 * Helper function that recusively goes left and right
 * and deletes all the node and memory
 */
void HCTree:: deleteNode(HCNode* n){
    if ( n != nullptr ) {
        // Recursively delete all children
        deleteNode( n->c0 );
        deleteNode( n->c1 );
	   delete n;
    }
    n = nullptr; 
}

/*
 * Deconstruct the whole tree.
 * Calls the helper function deleteNode
 * to recursively delete every node in the tree.
 */
HCTree::~HCTree(){ 
    // Deconstruct all 
    HCNode *d = this->root;
    if (d == 0)
        return;
    else {
        delete d -> c0;
        delete d -> c1;
        delete d;
    }

    for (unsigned int i = 0; i < leaves.size(); i++) {
        delete leaves[i];
    }
}

/** Use the Huffman algorithm to build a Huffman coding trie.
 *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
 *  the frequency of occurrence of byte i in the message.
 *  POSTCONDITION:  root points to the root of the trie,
 *  and leaves[i] points to the leaf node containing byte i.
 */
void HCTree:: build(const vector<int>& freqs){
    priority_queue<HCNode*, vector<HCNode*>,HCNodePtrComp> pq;
    vector<int>::const_iterator vit= freqs.begin();
    vector<int>::const_iterator ven= freqs.end();
    int counts,counter=0;
    HCNode* temp;
    HCNode* temp2;
    HCNode* temp3;
    HCNode* temp4;
    byte symbol = 0;
    
    for(; vit!=ven; vit++){
        if(*vit==0) { 
            //if freq is zero, meaning no byte exits, just skip
            counter++;
            continue;
        }
	
	    // index of the freq vector is our symbol
	    symbol = (char)counter;   // converts the counter into a symbol
        // create a new node with those attributes
	    temp = new HCNode(*vit, symbol); 
        
	    // Push the new node back onto the queue
        // where it will automatically be sorted
        pq.push(temp);
  
        // store the node pointer in the specified symbol location        
        this -> leaves[symbol] = temp;

        counter++;
    }
    
    while(pq.size() != 1){
    
    	//pop the two smallest element from the queue.	    
  	    temp2 = pq.top();
        //cout << "First node symbol: " << temp2 -> symbol << endl;
        pq.pop();
        temp3 = pq.top();

        //cout << " Second node symbol: " << temp3 -> symbol << endl;
        pq.pop();

        
	    //add their counts together 
        counts = temp2->count + temp3->count;

      	//create a new node with that count and the two previous nodes as child
       temp4 = new HCNode(counts, temp2->symbol < temp3->symbol ? 
        temp2 -> symbol: temp3 -> symbol, temp3, temp2);

        // Set the new node as the current childrens' parents
        temp2 -> p = temp4;
        temp3 -> p = temp4;
        	     
        // Push it on and sort again
        pq.push(temp4);          
    } 

    this -> root= pq.top();
    pq.pop();

    if (pq.size() == 0)
        delete pq;
}


/** Write to the given BitOutputStream
  *  the sequence of bits coding the given symbol.
  *  PRECONDITION: build() has been called, to create the coding
  *  tree, and initialize root pointer and leaves vector.
  */
void HCTree::encode(byte symbol, BitOutputStream& out) const{ 
    // Assign node to inputed byte
    HCNode *leafSym= this -> leaves[symbol]; 
	
	// Build from top to bottom
    std::stack<int> st;

    //cout << "starting loop" << endl;
	while(leafSym != this->root && leafSym != NULL){

        if (leafSym -> p -> c0 == leafSym) {
            st.push(0);
        }

        else if (leafSym -> p -> c1 == leafSym) {
            st.push(1);
        }
        leafSym = leafSym-> p;

    } 

    while (!st.empty()) {
        out.writeBit( st.top());
        st.pop();
    }
}

/** Return symbol coded in the next sequence of bits from the stream.
  *  PRECONDITION: build() has been called, to create the coding
  *  tree, and initialize root pointer and leaves vector.
  */
int HCTree::decode(BitInputStream& in) const{
	HCNode* node = this->root;
	unsigned int bitRead = 0;

	while ( node -> c0 != NULL || node-> c1 != NULL){
        // Get the bit from the stream
		bitRead = in.readBit();

		if(bitRead){
			node = node -> c1; // If bit is 1, go to right cild
        }
		else {
            node = node-> c0; // If bit is 0, go to left child
        }
	}

 	return node -> symbol; // Return the leaf's symbol
}


