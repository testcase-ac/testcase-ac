#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: the number of windows and people
    // Constraint: 1 ≤ N ≤ 2,100,000,000
    long long N = inf.readLong(1LL, 2100000000LL, "N");
    inf.readEoln();  // end of the single line containing N

    inf.readEof();   // no more input allowed
    return 0;
}
