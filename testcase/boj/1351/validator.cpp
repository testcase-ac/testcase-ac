#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, P, Q on a single line
    long long N = inf.readLong(0LL, 1000000000000LL, "N");
    inf.readSpace();
    long long P = inf.readLong(2LL, 1000000000LL, "P");
    inf.readSpace();
    long long Q = inf.readLong(2LL, 1000000000LL, "Q");
    inf.readEoln();

    // No further input
    inf.readEof();
    return 0;
}
