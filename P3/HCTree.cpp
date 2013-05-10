#include "HCTree.hpp"

/** Use the Huffman algorithm to build a Huffman coding trie.
  *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
  *  the frequency of occurrence of byte i in the message.
  *  POSTCONDITION:  root points to the root of the trie,
  *  and leaves[i] points to the leaf node containing byte i.
  */
void HCTree:: build(const vector<int>& freqs){
  //HCNode elements, using vector of HCNodes to store elements, HCNodePtrComp to  //compare elements
  priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;
  vector<int>::iterator vit = freqs.begin();
  vector<int>::iterator vend = freqs.end();
  HCNode* temp;
  HCNode* temp2;
  HCNode* temp3;
  HCNode* temp4;
  byte symbol = 0;


 //TODO
  for(; vit!=ven; vit++){
        //If freq is zero, meaning no bytes exist,
        //just continue back to forloop
	if(*vit == 0){
	counter++;
	 continue;
	}

	symbol = (char)counter; //converts counter into symbol
	temp = new HCNode*(*vit, symbol); //create node with those attributes

	//push it to queue where HCNodePtrComp method is used
	//to sort the queue from smallest to biggest
	pq.push(temp);

	//store the node pointer in the specified symbol location
	leave[counter] = temp;
	counter++;
   }

  while(pq.size != 1){
	//pop the two smallest element from queue
	temp2 = pq.pop();
	temp3 = pq.pop();
	
	//add counts together to create a sum of lowest #s
	counts = temp2->count + temp3->count;

	// create new node with that count and two previous nodes ad child
	temp4 = new HCNode(counts, temp2, temp3, temp4);

	//push it back into the queue sorts again
	pq.push(temp4);

	//repeat until only one node is left in the queue that node has 
	//whole tree
  }

 root = temp4;
}


/** Write to the given BitOutputStream
  *  the sequence of bits coding the given symbol.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
void B encode(byte symbol, BitOutputStream& out) const;

    /** Return symbol coded in the next sequence of bits from the stream.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
    int decode(BitInputStream& in) const;

