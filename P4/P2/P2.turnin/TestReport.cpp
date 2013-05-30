// Jane Doe <janedoe@ucsd.edu>, John Doe <johndoe@ucsd.edu>
// This is a version of the Report function for use in a minimal turnin test
//
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <vector>

extern std::vector<int64_t> candidates;
extern std::vector<bool> primeFlags;
//131821332649496549=412426037*319624177  not prime
//1459337540551819969 prime
//3293201=1783*1847 not a prime
//1059251 prime
int64_t testNumbers[]={13,100,1059251,3293201}; 
bool testFlags[]={true,false,true,false};

void ReportPrimes(int n){
    // Check against a known test set. Output nothing if all is correct.

    for (int i=0;i<n; i++) {
      if(primeFlags[i]!=testFlags[i]) {
	std::cerr << "error: the number :" << testNumbers[i] << " is " 
		  << (testFlags[i]?"prime":"not prime")  << std::endl;
        }
    }
}
