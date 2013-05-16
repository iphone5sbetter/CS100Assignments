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
        int numSymbolz = 0;
        int textLength = 0;

        do {
            bytez = (*inputstream).readByte();
            if (bytez != -1) {
                ++(freq[bytez]);
            }            
        } while (bytez != -1);


        for (int i = 0; i < 256; i++)
        {
            if (freq[i] != 0) {
                numSymbolz++;
                textLength += freq[i];
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

        int headerlength = numSymbolz * 5 + 8;
        cout << "Writing the length of the header: " << headerlength << endl;
        fileout.write((char*)&headerlength,4);
        //outputstream -> writeInt(headerlength);

        cout << "Writing # of unique symbols " << numSymbolz << endl;
        fileout.write((char*)&numSymbolz,4);
        //outputstream -> writeInt(numSymbolz);
        
        cout << "Writing length of text (bytes) " << textLength << endl;
        fileout.write((char*)&textLength,4);

        cout << "Writing main header" << endl;
        for (unsigned int i = 0; i < freq.size(); i++) {
            if (freq[i] > 0) {

                cout << " number: " << freq[i] << endl;
                // Write the number of them
                fileout.write((char*)&freq[i],4);

                //outputstream -> writeInt(freq[i]);
                // Write the byte
                (*outputstream).writeByte((char)i);  
                cout << " byte: " << i << endl; 
            }
        }


        //cout << "Compressing..." << endl;
        int sym = 0;
        while (filein.good()) {
            sym = (*inputstream).readByte();
            tree -> encode((byte)sym, *outputstream);
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

