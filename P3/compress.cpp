#include <vector>
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include "BitInputStream.hpp"
#include "HCTree.hpp"

using namespace std;

ifstream::pos_type size;
vector<int>freq(256); // 256 different combinations of bits

char *memblock;

int main(int argc, char *argv[]) {

    // Handle input
    ifstream filein;
    filein.open(argv[1], ios::binary);

    // Handle output
    ofstream fileout;
    fileout.open ("test.txt", ios::binary | ios::out);

    //ifstream file (argv[1], ios::binary);

    if (filein.is_open())
    {
        BitInputStream *inputstream = new BitInputStream(filein);
       
        // read in bits/bytes here
        
        int bytez;
        do {
            bytez = (*inputstream).readByte();
            if (bytez != -1)
                ++(freq[bytez]);
            //cout << "Byte: " << bytez << endl;
            
        } while (bytez != -1);
        
        filein.close();
    }
    else if (filein.bad()) {
        cout << "Error opening the file\n" << endl;
    }
    else {
        cout << "File Not Found\n";
    }

    for (int i = 0; i < 256; i++)
    {
        if (freq[i] != 0) {
            cout << "Index: " << i << " " << "Freq: " << freq[i] << endl;
        }
    }
    
    // Build the tree
    HCTree *tree = new HCTree();
    (*tree).build(freq);

    BitOutputStream *outputstream = new BitOutputStream(fileout);

    /*
    // Encode each byte
    for (int i = 0; i < 255; i++) {
        (*tree).encode((char)i, *outputstream);
    }
    */

}

