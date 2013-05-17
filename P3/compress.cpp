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

        cout << "counting bytes" << endl;
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

        cout << "building tree "<< endl;
        // Build the tree
        HCTree *tree = new HCTree();
        (*tree).build(freq);

        // Handle output
        ofstream fileout;
        fileout.open(argv[2], ios::binary);

        BitOutputStream *outputstream = new BitOutputStream(fileout);
        filein.clear();
        filein.seekg(0, ios::beg);

        cout << "Writing # of unique symbols " << numSymbolz << endl;
        fileout.write((char*)&numSymbolz,4);
                
        cout << "Writing length of text (bytes) " << textLength << endl;
        fileout.write((char*)&textLength,4);

        cout << "writing header bytes" << endl;
        for (unsigned int i = 0; i < freq.size(); i++) {
            if (freq[i] > 0) {
                fileout.write((char*)&freq[i],4);
                (*outputstream).writeByte((char)i);  
            }
        }

        cout << "reading/writing main bits" << endl;
        int sym = 0;
        int y = 0;
        while (filein.good() && y < textLength) {
            sym = (*inputstream).readByte();
            tree -> encode((byte)sym, *outputstream);
            y++;
            cout << y << endl;
        }
        cout << "finished main bits " << endl;
        outputstream -> flush();
        
        delete tree;

        filein.close();
        fileout.close();
    }
    else if (filein.bad()) {
        cout << "Error opening the file\n" << endl;
    }
    else {
        cout << "File Not Found\n";
    }

    }

    else {
        cout << "File error - try again" << endl;
    }
}

