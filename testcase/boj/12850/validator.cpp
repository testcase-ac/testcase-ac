#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read D: the length of the walk (1 ≤ D ≤ 1e9)
    long long D = inf.readLong(1LL, 1000000000LL, "D");
    inf.readEoln();

    // No further input
    inf.readEof();
    return 0;
}
