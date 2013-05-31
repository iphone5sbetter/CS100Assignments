// Daniel Brim <dbrim@ucsd.edu>, Tyler Pollak <cs100tak@ieng6.edu>
#include "BitOutputStream.hpp"

 /** Write the least significant bit of the argument into
   *  the bit buffer, and increment the bit buffer index.
   *  Flush to the ostream first if the bit buffer is full.
   *  This must be consistent with BitInputStream::readBit().
   */
void BitOutputStream:: writeBit(int bit){
    // Buffer is full, write it
	if(bufi == 0){
	    flush(); // Write out
        buf = 0;
        bufi = 0x80; // Reset the mask
	}
    if (bit == 1) 
        buf |= bufi;
    
    bufi >>= 1;
}

  /** Write the least significant byte of the argument to the ostream.
   *  This function doesn't touch the bit buffer.
   *  The client has to manage interaction between writing bits
   *  and writing bytes.
   */
void BitOutputStream:: writeByte(int b){
    // Write a byte with put().
    out.put(b);  
}

  /** Write the argument to the ostream.
   *  This function doesn't touch the bit buffer.
   *  The client has to manage interaction between writing bits
   *  and writing ints.
   */
void BitOutputStream:: writeInt(int i){
    // Just write the int
    out.write((char*)&i, 4);
}

/**
 * This method performs the writing of the bit buffer 
 * to the file stream.
 */
void BitOutputStream:: flush(){
    out.put(buf);
}

