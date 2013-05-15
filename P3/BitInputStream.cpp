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

 //if buffer index == 0
 if(bufi == 8){
   buf = in.get();
   bufi = 0;
}

 // EOF reached
 if(in.eof()){
   return -1;
 }
 
 //decrement buffer index as you move down the array
 bufi++;
 int index = 8 - bufi;
 return (buf &(1<<index));

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
    unsigned int num = 0;

    int temp = readByte();
    num = temp;
    cout << "num: " << temp << endl;

    temp = readByte();
    num = num << 8;
    num = num | temp;
    cout << "num: " << temp << endl;

    temp = readByte();
    num = num << 8;
    num = num | temp;
cout << "num: " << num << endl;
    temp = readByte();
    num = num << 8;
    num = num | temp;
cout << "num: " << num << endl;
    return num;
}



