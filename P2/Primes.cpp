#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <vector>
#include <thread>

// Tests list of numbers for primality
// Usage: a.out n1 [n2...]
// Where the n_i are numbers to be tested for primality
// Scott B. Baden, UCSD, 17 April 2013
//
// Use this web page to test for primarility and generate
// lists of prime numbers in the vicitinty of a given number
// http://markknowsnothing.com/cgi-bin/primes.php
//

// Globals, shared by all threads
//
// DO NOT change these declarations as we rely on them to grade your assignment
//
// Candidate primes
std::vector<int64_t> candidates;
// Identify which number(s) is (are) prime
std::vector<bool> primeFlags;

//
// DO NOT change the signatures of these 4 functions as we will rely on
// them to test your assignment

// TODO: Write this routine to show the output of your prime number tester
void ReportPrimes(int n);

void getInput(int argc, char *argv[], int &n, int &NT);

// The thread function
void prime_th(int TID, int NT, int n);

// A timer
double getTime();

//
// End declaration of 4 functions
//

//
// --- Main module
//
int main(int argc, char *argv[]) {
    int n, NT;

    // Sets the number of candidate primes to test
    // and the number of threads
    // TODO: Follow further instructions in getInput()
    getInput(argc,argv,n,NT);

    // Start the timer
    double t0 = getTime();

    // Read in each number, report on primality
    // TODO: write a thread function to read in
    // values from the vector setup by getInput
    // such that each thread samples its own section of the vector.
    // The first argument specifies the thread ID, the second
    // the number of threads, the third, the number of primes.
    // The thread function will divide the n primes into
    // disjoint subsets, giving each thread exactly one subset

    //Default constructor of class thread
    //Creates a receptacle but not the actual thread
    std::thread *thrds = new std::thread[NT];
    for(int t = 0; t< NT; t++){
	//Spawn threads
	//Creates thread object & associates it with a thread of execution
	//Thread runs prime_th()
	thrds[t] = std::thread(prime_th, t, NT, n);
    }
    //Join threads
    for(int t = 0; t < NT; t++){
	thrds[t].join();
    }

    //prime_th(0, NT, n); //only 1 thread, REMOVE LATER
    

    // Stop the Timer
    double t1 = getTime();

    // Report the timings
    std::cout << "Testing the candidate primes " << " took ";
    std::cout << "  " << t1-t0 << " seconds";
    std::cout << "  on " << NT << " threads" << std::endl;
   // std::cout << "#> " << argc << " " << 


    std::cout << std::endl;
}
