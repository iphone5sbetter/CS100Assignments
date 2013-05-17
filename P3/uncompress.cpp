#include "HCTree.hpp"
#include <fstream>

int main(int argc, char* argv[]){
   int numOfChar=0;
   int symbol=0;
   int symchar=0;
   int symbol2 = 0;
   int counter = 0;
   vector<int>freq = vector<int>(256, 0);
   std::ofstream outfile;
   std::ifstream infile;
  
    if(argc !=3){
	    //std::cout << argv[0] << " called with incorrect arguments. "<< std::endl;
	    //std::cout << "Usage:" << std::endl;
	    //std::cout << argv[0] << " infile outfile" << std::endl;
    	exit(-1);
    }

    infile.open(argv[1], ios::binary); // Open input file
    outfile.open(argv[2], ios::binary); // Open output file

	BitInputStream* input = new BitInputStream(infile);
    BitOutputStream* output = new BitOutputStream(outfile);

    if(infile.is_open()) {
        //unsigned int hlength = input -> readInt(); // Length of header (bytes)
        unsigned int tlength = input -> readInt(); // Length of text (bytes)
        unsigned int textbytes = input -> readInt();

        //std::cout << "Length of header " << hlength << std::endl;
        //std::cout << "Num of diff symbols " << tlength << std::endl;
        //std::cout << "Length of text (bytes) " << textbytes << endl;
        /******* header ********/

        /// BUILD HEADER //
	    unsigned int i = 0; // Start past the two nums, at the actual header
        while( i < tlength) {
            int d = input -> readInt();
            int s = input -> readByte();
            //std::cout << "Symbol " << s << endl;
            //std::cout << "Number of them: " << d << endl;
            
            freq[s] = d;
            i++;
       } 
        
       //cout << "here 1" << endl; 
          //Build tree here.
        
        HCTree* myTree = new HCTree();
        myTree->build(freq);


          //Decode individual bytes
         
        int y = 0;
        //cout << "" << endl;
        // && y < textbytes
        while (infile.good() && y < textbytes) {
            int decoded = myTree -> decode(*input);
            //cout << "Decoded byte: " << (unsigned char)decoded << endl;
            outfile.put((unsigned char)decoded);
            y++;
        }
        outfile.flush();
    }

    infile.close();
}
    
