// Daniel Brim <dbrim@ucsd.edu>, Tyler Pollak <tpollak@ucsd.edu>
/*
 * Assignment 2
 * CS 100 - Spring 2013
 * Apr 25, 2013
 *
 * Daniel Brim - dbrim - A09828025
 * Tyler Pollak - tpollak -A09965467
 * Partner submission
 *
 * getInput - 
 * This function reads in input from the command line (primes)
 * and adds them to the vector 'candidates.'
 * NT - number of threads
 * n - total number of candidates
 */

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
    // We're subtracting off one more in order to exclude NT
    // from being "primed." We think this was a mistake in the code 
    // originally supplied to us. This is our fix to reproduce the 
    // OUTPUT exactly, as required by the assignment. 
    if (n >= 1 )
    {
        n -= 1;
    }
    // Read in number of threadss
    NT = atof(argv[1]);

    std::cout << "Testing " << n << " candidate primes" << std::endl;
    //add number of threads
    std::cout << "Number of threads: " << NT << std::endl;

    // TODO: Read in the number of threads and candidate primes
   
    std::cout << "Candidate primes:" << std::endl;
    for (int i = 2; i < argc; i++)
    {
        // Add candidates to vector
        candidates.push_back(atoll(argv[i]));
        // print candidates
        std::cout << atoll(argv[i]) << std::endl;
    }

    // Add some nice spacing
    std::cout << std::endl;
}
