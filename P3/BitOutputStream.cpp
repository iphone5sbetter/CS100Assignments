#include "BitOutputStream.hpp"




 /** Write the least significant bit of the argument into
   *  the bit buffer, and increment the bit buffer index.
   *  Flush to the ostream first if the bit buffer is full.
   *  This must be consistent with BitInputStream::readBit().
   */
void BitOutputStream:: writeBit(int bit){
	if(bufi == 8){
	    flush();
        cout << "Flushing..." << endl;
	}

	int index = 7-bufi;
	buf = buf | (bit<< index);
	bufi++;
}

  /** Write the least significant byte of the argument to the ostream.
   *  This function doesn't touch the bit buffer.
   *  The client has to manage interaction between writing bits
   *  and writing bytes.
   */
void BitOutputStream:: writeByte(int b){

}

  /** Write the argument to the ostream.
   *  This function doesn't touch the bit buffer.
   *  The client has to manage interaction between writing bits
   *  and writing ints.
   */
void BitOutputStream:: writeInt(int i){

}

void BitOutputStream:: flush(){

 	out.put(buf);
	out.flush();
	bufi=0;
	buf=0;

}

