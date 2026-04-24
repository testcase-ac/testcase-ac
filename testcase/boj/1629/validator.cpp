#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read A, B, C: natural numbers between 1 and 2,147,483,647 inclusive.
    long long A = inf.readLong(1LL, 2147483647LL, "A");
    inf.readSpace();
    long long B = inf.readLong(1LL, 2147483647LL, "B");
    inf.readSpace();
    long long C = inf.readLong(1LL, 2147483647LL, "C");
    
    // The line should end here
    inf.readEoln();
    
    // No extra input
    inf.readEof();
    
    return 0;
}
