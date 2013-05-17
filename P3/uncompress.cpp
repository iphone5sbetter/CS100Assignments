#include "HCTree.hpp"
#include <fstream>

std::ofstream outfile;
std::ifstream infile;
vector<int>freq = vector<int>(256, 0);

int main(int argc, char* argv[]){
    if (argc != 3) {
	    std::cout << argv[0] << " called with incorrect arguments. "<< std::endl;
	    std::cout << "Usage:" << std::endl;
	    std::cout << argv[0] << " infile outfile" << std::endl;
    	exit(-1);
    }

    infile.open(argv[1], ios::binary); // Open input file
    outfile.open(argv[2], ios::binary); // Open output file

	BitInputStream* input = new BitInputStream(infile);
    //BitOutputStream* output = new BitOutputStream(outfile);

    if(infile.is_open()) {
        //unsigned int hlength = input -> readInt(); // Length of header (bytes)
        unsigned int tlength = input -> readInt(); // Length of text (bytes)
        int textbytes = input -> readInt();

        // BUILD HEADER //
	    unsigned int i = 0; // Start past the two nums, at the actual header
        while( i < tlength) {
            int d = input -> readInt();
            int s = input -> readByte();
            
            freq[s] = d;
            i++;
       } 
        
        HCTree* myTree = new HCTree();
        myTree->build(freq);

        //Decode individual bytes
         
        int y = 0;
        while (infile.good() && y < textbytes) {
            int decoded = myTree -> decode(*input);
            outfile.put((unsigned char)decoded);
            y++;
        }
        outfile.flush();
    }

    infile.close();
}
    
