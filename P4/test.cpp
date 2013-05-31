#include <ostream>
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

main(void) {

    double d = 3.14;
    ofstream of1;
    of1.open("out1", ios::binary);
    of1 << setw(12) << d;
    of1.close();

    ofstream of2;
    of2.open("out2", ios::binary); 
    of2.write((char*)&d, sizeof(d));
    of2.close();
    
}