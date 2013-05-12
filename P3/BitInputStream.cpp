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
 //if buffer is empty, populate array with byte and set bufi to 0
 if(buf == 0){
  //in.get() gets 1 byte at a time
   buf = in.get();
   bufi = 8;
 }

 //if buffer index == 0
 if(bufi == 0){
   buf = in.get();
   bufi = 8;
}

 // EOF reached
 if(in.eof()){
   return -1;
 }
 
 int index = bufi -1;
 char mask = 1;

 //decrement buffer index as you move down the array
 bufi--;
 return (buf &(1<<index)) >>index;

}


/** Read a byte from the ostream.
  *  Return -1 on EOF.
  *  This function doesn't touch the bit buffer.
  *  The client has to manage interaction between reading bits
  *  and reading bytes.
  */
int BitInputStream:: readByte(){
    int byte = in.get();

    if (in.eof())
        return -1;

    return byte;
}

/** Read a non-negative int from the ostream.
  *  Return -1 on EOF.
  *  This function doesn't touch the bit buffer.
  *  The client has to manage interaction between reading bits
  *  and reading ints.
  */
int BitInputStream:: readInt(){

}



