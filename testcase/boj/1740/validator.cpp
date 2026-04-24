#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: the N-th smallest number representable as a sum of distinct powers of 3
    long long N = inf.readLong(1LL, 500000000000LL, "N");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
