// Daniel Brim <dbrim@ucsd.edu>, Tyler Pollak <tpollak@ucsd.edu>
#include <stdlib.h>
/*
 * Assignment 2
 * CS 100 - Spring 2013
 * Apr 25, 2013
 *
 * Daniel Brim - dbrim - A09828025
 * Tyler Pollak - tpollak -A09965467
 * Partner submission
 *
 * ReportPrimes - 
 * prints out all of the numbers that are primes
 */

#include <assert.h>
#include <iostream>
#include <vector>

// Globals, shared by all threads
// DO NOT change these declarations as we rely on them to grade your assignment
//
// Candidate primes
extern std::vector<int64_t> candidates;
// Identify which number(s) is (are) prime
extern std::vector<bool> primeFlags;

// TODO: Write this routine to show the output of your prime number tester
void ReportPrimes(int n){

    // Count how many primes are there are
    int counter = 0;
    for (int i = 0; i < n; i++) {
        if (primeFlags[i] == true) {
            counter++;
        }
    }

    // Print out the primes
    std::cout << "A total of " << counter << " primes were identified" << std::endl;

    for (int i = 0; i < n; i++) {
        if (primeFlags[i])
            std::cout << candidates[i] << " is a prime number" << std::endl;
    }
}
