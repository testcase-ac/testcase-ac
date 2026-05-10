#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single test case (problem statement gives only one N,K)
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    long long K = inf.readLong(1LL, 1000000000LL, "K");
    inf.readEoln();

    // No further input is specified by the statement, so nothing more to read.

    inf.readEof();
}
