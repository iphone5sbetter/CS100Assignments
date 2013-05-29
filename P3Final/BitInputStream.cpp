// Daniel Brim <dbrim@ucsd.edu>, Tyler Pollak <cs100tak@ieng6.edu>

#include "BitInputStream.hpp"

/** Read the next bit from the bit buffer.
  *  If the bit buffer is currently empty,
  *  fill the bit buffer by reading a char from the istream first.
  *  Return the bit read as the least signficant bit of an int.
  *  Return -1 on EOF.
  *  This must be consistent with BitOutputStream::writeBit(), in terms
  *  of ordering of bits in the stream.
  */
int BitInputStream:: readBit(){

    // Buffer is empty, refill it
    if (bufi == 8) {
        buf = in.get();
        bufi = 0;
    }

    // EOF reached
    if(in.eof()){
        return -1;
    }

    // Shift to get the bit we need.
    unsigned int temp =  buf & (1 << (7 - bufi));
    bufi++;
    if (temp != 0)
        temp = 1;
    else
        temp = 0;
    return temp;
}


/** Read a byte from the ostream.
  *  Return -1 on EOF.
  *  This function doesn't touch the bit buffer.
  *  The client has to manage interaction between reading bits
  *  and reading bytes.
  */
int BitInputStream:: readByte(){
    if (in.eof())
        return -1;
    // No error, just return a byte
    return in.get();
}

/** Read a non-negative int from the ostream.
  *  Return -1 on EOF.
  *  This function doesn't touch the bit buffer.
  *  The client has to manage interaction between reading bits
  *  and reading ints.
  */
int BitInputStream:: readInt(){
    unsigned int temp = 0; 
    
    // Read a byte in from the file
    in.read((char*)&temp, 4);
    if (in.eof())
        return -1;
    return temp;
}



