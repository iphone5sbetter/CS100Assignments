#include "HCTree.hpp"
#include <stack>

/**Helper function that recusively goes left and right
 * and deletes all the node and memory
 */
void HCTree:: deleteNode(HCNode* n){
	if ( n != nullptr ) {
           deleteNode( n->c0 );
           deleteNode( n->c1 );
	   delete n;
    }
    n = nullptr; 
}

HCTree::~HCTree(){ 
    HCNode *d = this->root;
    if (d == 0)
        return;
    else {
        delete d -> c0;
        delete d -> c1;
        delete d;
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
        if(*vit==0) { //if freq is zero, meaning no byte exits, just skip
          counter++;
          continue;
        }
	
	    //index of the freq vector is our symbol
	    symbol = (char)counter;   //converts the counter into a symbol
        /********************/
        //cout << "Symbol: " << symbol;
        //cout << " with count:" << *vit << endl;

	    temp = new HCNode(*vit, symbol); //create a new node with those attributes
        

	    //push it to the queue where it will use the HCNodePtrComp method 
	    //to sort the queue from smallest to biggest
        pq.push(temp);
  
        //store the node pointer in the specified symbol location        
        this->leaves[symbol]= temp;

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
        //temp4 = new HCNode(counts, temp2->symbol < temp3->symbol ? temp2 -> symbol: temp3 -> symbol, temp3, temp2);
        temp4 = new HCNode(counts, temp2->symbol < temp3->symbol ? temp2 -> symbol: temp3 -> symbol, temp3, temp2);

        temp2 -> p = temp4;
        temp3 -> p = temp4;


        
        //cout << " Added node symbol: " << temp4 -> symbol << endl;
	    //setting parents
	     
        //push it back into the queue, queue sorts again.
        pq.push(temp4);      

        //repeat until only one node is left in the queue and that node has 
        //the whole tree
        //
    } 

    this -> root= pq.top();
    //pq.pop();
    
}


/** Write to the given BitOutputStream
  *  the sequence of bits coding the given symbol.
  *  PRECONDITION: build() has been called, to create the coding
  *  tree, and initialize root pointer and leaves vector.
  */
void HCTree::encode(byte symbol, BitOutputStream& out) const{ 
    HCNode *leafSym= this -> leaves[symbol]; //assigns a node to the inputed symbol
	
	//builds from bottom to top
	//stops when it is at root
    std::stack<int> st;

    //cout << "starting loop" << endl;
	while(leafSym != this->root && leafSym != NULL){

	    // checks whether it is the c0 child of parent
	    // if it is, set leafSym to parent
	    // set default temSym to keep track of the bit
	    // in this case, the bit is 0
	    // dincrement and decrement index and counter

        if (leafSym -> p -> c0 == leafSym) {
            st.push(0);
        }
	 
	    // checks whether it is the c1 child of parent
	    // if it is, set leafSym to parent
	    // set default temSym to keep track of the bit
	    // in this case, the bit is 1
	    // increment and decrement index and coutner

        else if (leafSym -> p -> c1 == leafSym) {
            st.push(1);
        }
        leafSym = leafSym-> p;

    } 
    //cout << "ending loop" << endl;

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

    // probably here or readBit, not reading enough bits for long codes
	while ( node -> c0 != NULL || node-> c1 != NULL){
		bitRead = in.readBit(); //get the byte from the input stream

		if(bitRead){
			node = node -> c1; // if bit read is 1, go c1 child
            //cout << "Going to right child" << endl;
		}
		else {
            node = node-> c0; // if bit read is 0, go g0 child	
           // cout << "Going to left child" << endl;
        }
	}

    //cout << "Decoding byte: " << node -> symbol << endl;
 	return node -> symbol; //return the symbol at the end of the tree
	
}
