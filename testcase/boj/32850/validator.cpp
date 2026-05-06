#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single integer n, 1 ≤ n ≤ 10^12
    long long n = inf.readLong(1LL, 1000000000000LL, "n");
    inf.readEoln();  // end of line after n

    inf.readEof();   // no more input
    return 0;
}
