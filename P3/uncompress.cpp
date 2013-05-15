#include "HCTree.hpp"
#include <fstream>

int main(int argc, char* argv[]){
   int numOfChar=0;
   int symbol=0;
   int symIndex=0;
   int symbol2 = 0;
   int counter = 0;
   vector<int>freqs= vector<int>(256, 0);
   std::ofstream outfile;
   std::ifstream infile;
  
    if(argc !=3){
	std::cout << argv[0] << " called with incorrect arguments. "<< std::endl;
	std::cout << "Usage:" << std::endl;
	std::cout << argv[0] << " infile outfile" << std::endl;
	exit(-1);
    }

    infile.open(argv[1], ios::binary); // Open input file
    outfile.open(argv[2], ios::binary); // Open output file

	BitInputStream* input = new BitInputStream(infile);

    if(infile.is_open()) {
        
        unsigned int first = input -> readInt(); //number of characters

        cout << "first " << first << endl;

        numOfChar = symbol - 48;
	
        while(counter <= numOfChar){
	        symbol = input->readByte(); 	//number of occurences 
            std::cout << "symbol: " << symbol<<std::endl;

	        symbol -= 48;	
	        symIndex = input->readByte(); 	//the symbol/character
            std::cout<<"symIndex: "<<symIndex<<std::endl;
	        freqs[(byte)symIndex]= symbol;
	        symbol=symIndex;
	        counter++;
        }	
    }

     //HCTree* myTree = new HCTree();
     //myTree->build(freqs);

     //BitInputStream* input = new BitInputStream(in);
/*
    while(infile.good()){
    	symbol2 = myTree->decode(*input);
        outfile.put((char)symbol2);
	    std::cout<<"asd"<<std::endl;	
    } */
	
    infile.close();
    
}
