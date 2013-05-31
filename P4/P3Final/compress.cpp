// Daniel Brim <dbrim@ucsd.edu>, Tyler Pollak <cs100tak@ieng6.edu>
#include <vector>
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include "BitInputStream.hpp"
#include "HCTree.hpp"

using namespace std;

ifstream::pos_type size;
vector<int>freq(256, 0); // 256 different combinations of bits
BitInputStream *inputstream;

int main(int argc, char *argv[]) {

    if (argc > 2 ) {

    // Handle input
    ifstream filein;
    filein.open(argv[1], ios::binary);

    if (filein.is_open())
    {
        inputstream = new BitInputStream(filein);
       
        // read in bits/bytes here 
        int bytez = 0;
        int numSymbolz = 0;
        int textLength = 0;

        do {
            bytez = filein.get();
            if (bytez != -1) {
                ++freq[bytez];
            }            
        } while (bytez != -1);

        for (int i = 0; i < 256; i++)
        {
            if (freq[i] != 0) {
                numSymbolz++;
                textLength += freq[i];
            }
        }
        
        // Build the tree
        HCTree *tree = new HCTree();
        (*tree).build(freq);

        // Handle output
        ofstream fileout;
        fileout.open(argv[2], ios::binary);

        BitOutputStream *outputstream = new BitOutputStream(fileout);
        filein.clear();
        filein.seekg(0, ios::beg);

        // Write the number of unique symbols
        fileout.write((char*)&numSymbolz,4);
        // Write length of the original text
        fileout.write((char*)&textLength,4);

        for (unsigned int i = 0; i < freq.size(); i++) {
            if (freq[i] > 0) {
                fileout.write((char*)&freq[i],4);
                (*outputstream).writeByte((char)i);  
            }
        }

        int sym = 0;
        int y = 0;
        // Read the bytes and encode them
        while (filein.good() && y < textLength) {
            sym = (*inputstream).readByte();
            tree -> encode((byte)sym, *outputstream);
            y++;
        }

        // Finish writing the encoded file
        outputstream -> flush();
        
        delete tree;
        delete inputstream;
        delete outputstream;
        
        // Close the files
        filein.close();
        fileout.close();
    }
    else {
        std::cout << argv[0] << " called with incorrect arguments. "<< std::endl;
	    std::cout << "Usage:" << std::endl;
	    std::cout << argv[0] << " infile outfile" << std::endl; 
    }
    }

    else {
        std::cout << argv[0] << " called with incorrect arguments. "<< std::endl;
	    std::cout << "Usage:" << std::endl;
	    std::cout << argv[0] << " infile outfile" << std::endl;
    }
}

