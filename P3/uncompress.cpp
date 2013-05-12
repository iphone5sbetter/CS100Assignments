#include <vector>
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include "BitInputStream.hpp"

using namespace std;

ifstream::pos_type size;
vector<int>freq(256); // 256 different combinations of bits

char *memblock;

int main(int argc, char *argv[]) {

    ifstream file;
    file.open(argv[1], ios::binary);
    //ifstream file (argv[1], ios::binary);
    if (file.is_open())
    {
        BitInputStream *inputstream = new BitInputStream(file);
        // read in bits/bytes here
        
        int bytez;
        do {
            bytez = (*inputstream).readByte();
            if (bytez != -1)
                ++(freq[bytez]);
            //cout << "Byte: " << bytez << endl;
            
        } while (bytez != -1);
        
        file.close();
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
}

