// Daniel Brim <dbrim@ucsd.edu>, Tyler Pollak <cs100tak@ieng6.edu>
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

    if(infile.is_open()) {

        // Read the number of unique bytes
        unsigned int tlength = input -> readInt(); 
        // Read the length of the original text
        int textbytes = input -> readInt();

        // Read the frequencies of each byte from the header
	    unsigned int i = 0; // Start past the two nums, at the actual header
        while( i < tlength) {
            int d = input -> readInt();
            int s = input -> readByte();
            
            freq[s] = d;
            i++;
       } 
        
       // Build the tree from the frequencies
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
    else {
        std::cout << argv[0] << " called with incorrect arguments. "<< std::endl;
	    std::cout << "Usage:" << std::endl;
	    std::cout << argv[0] << " infile outfile" << std::endl;
    	exit(-1);
    }

    infile.close();
    outfile.close();
}
    
