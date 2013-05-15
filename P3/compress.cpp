#include <vector>
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include "BitInputStream.hpp"
#include "HCTree.hpp"

using namespace std;

ifstream::pos_type size;
vector<int>freq(256); // 256 different combinations of bits

char *memblock;
BitInputStream *inputstream;

int main(int argc, char *argv[]) {

    if (argc > 2 ) {

    // Handle input
    ifstream filein;
    filein.open(argv[1], ios::binary);

    // Handle output
    ofstream fileout;
    fileout.open (argv[2], ios::binary);

    //ifstream file (argv[1], ios::binary);

    if (filein.is_open())
    {
        inputstream = new BitInputStream(filein);
       
        // read in bits/bytes here 
        int bytez;
        int numSymbolz;

        do {
            bytez = (*inputstream).readByte();
            if (bytez != -1) {
                ++(freq[bytez]);
            }
            //cout << "Byte: " << bytez << endl;
            
        } while (bytez != -1);


        for (int i = 0; i < 256; i++)
        {
            if (freq[i] != 0) {
                numSymbolz++;
                cout << "Index: " << i << " " << "Freq: " << freq[i] << endl;
            }
        }

        // Build the tree
        HCTree *tree = new HCTree();
        (*tree).build(freq);

        BitOutputStream *outputstream = new BitOutputStream(fileout);
        filein.clear();
        filein.seekg(0, ios::beg);

        cout << "Writing first bytes..." << endl;

        cout << "Writing the first index of the header" << endl;
        int headerlength = numSymbolz*5 + 8;
        fileout.write((char*)&headerlength,4);

        cout << "Writing # of bytes in original text" << endl;
        fileout.write((char*)&numSymbolz,4);

        cout << "Writing main header" << endl;
        for (int i = 0; i < freq.size(); i++) {
            if (freq[i] > 0) {
                //cout << " byte: " << i << endl;

                // Write the number of them
                fileout.write((char*)&freq[i],4); 
                // Write the byte
                (*outputstream).writeByte((char)i);   
                
                //cout << " number: " << freq[i] << endl;
            }
        }


        cout << "Compressing..." << endl;
        int sym = 0;
        while (filein.good()) {
            sym = (*inputstream).readByte();
            (*tree).encode((byte)sym, *outputstream);
        }
        
        
    }
    else if (filein.bad()) {
        cout << "Error opening the file\n" << endl;
    }
    else {
        cout << "File Not Found\n";
    }

    filein.close();
    fileout.close();
    }

    else {
        cout << "File error - try again" << endl;
    }
}

