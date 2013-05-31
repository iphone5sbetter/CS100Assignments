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
 * prime_th - 
 * This function takes in a thread id, the total number of threads, 
 * and the total number of prime candidates. It figures out how many
 * primes it has to do based on the total number of candidates / number threads.
 * If a candidate is prime, it sets primeFlags to true for that vector.
 */

#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <thread>
#include <vector>


bool isPrime(int64_t x);

// Shared globals, allocated before threads are spawned
// These will be used in the threaded code
extern std::vector<int64_t> candidates; // Candidate primes
extern std::vector<bool> primeFlags;    // Prime flags

// This is the "thread function" that will be called by a newly created thread
// This provided code currently runs on only 1 thread
// TODO:
// Change this code to subdivide the n primes into disjoint sets
// properly handling the case whtn the number of threads doesn't divide N
//
//
// DO NOT change the signature for this code as we rely on
// it to test your assignment
//
// 
// This function should perform no I/O when you are timing the code
void prime_th(int TID, int NT, int n)
{
    int start = TID * (n / NT);
    int end = (TID + 1) * (n / NT);

    if (TID == (NT - 1)) {
        end = n;
    }
    
    for (int i = start; i < end; i++) {
        if (isPrime (candidates[i])){
           primeFlags[i] = true;
        }
    }
}
