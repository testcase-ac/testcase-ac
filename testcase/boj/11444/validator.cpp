#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n: a natural number (positive integer) <= 10^18
    long long n = inf.readLong(1LL, 1000000000000000000LL, "n");
    // After n, there must be exactly one end-of-line
    inf.readEoln();
    // And then immediately EOF
    inf.readEof();

    return 0;
}
