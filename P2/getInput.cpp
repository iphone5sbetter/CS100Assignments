#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <vector>

// Global shared vectors 
extern std::vector<int64_t> candidates;
extern std::vector<bool> primeFlags; 

// TODO: This code currently reads only the number of candidate primes
// off the command line
// You need to add code read in the number of threads and also to read
// athe candidate primes into a vector
//
// e.g. If we run ./primes 2 5 7,
// the number of threads (NT) is 2
// and the candidates are 5 and 7
//
//
// DO NOT change the signature for this code as we rely on
// it to test your assignment
//
void getInput(int argc, char *argv[], int &n, int &NT){
    n = argc; n -= 1;

    // The original code was just n -= 1 which
    // ended up including NT in the prime calculations.
    // We're subtracting off one more inorder to exclude NT
    // from being "primed." We think this was a mistake in the code 
    // originally supplied to us. This is our fix to reproduce the 
    // OUTPUT exaclty. 
    if (n >= 1 )
    {
        n -= 1;
    }

    std::cout << "Testing " << n << " candidate primes" << std::endl;

    // TODO: Read in the number of threads and candidate primes
   
    for (int i = 2; i < argc; i++)
    {
        candidates.push_back(*argv[i]);
    }

    NT = atof(argv[1]);
}
