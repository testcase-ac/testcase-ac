#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: 100 ≤ N ≤ 2,000,000,000
    long long N = inf.readLong(100LL, 2000000000LL, "N");
    inf.readEoln();

    // Read F: 1 ≤ F ≤ 100
    int F = inf.readInt(1, 100, "F");
    inf.readEoln();

    // No further input
    inf.readEof();
    return 0;
}
