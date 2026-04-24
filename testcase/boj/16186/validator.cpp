#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read and validate A, B, C, D on one line
    long long A = inf.readLong(1LL, 1000000000000LL, "A");
    inf.readSpace();
    long long B = inf.readLong(A, 1000000000000LL, "B");
    inf.readSpace();
    long long C = inf.readLong(1LL, 1000000000000LL, "C");
    inf.readSpace();
    long long D = inf.readLong(C, 1000000000000LL, "D");
    inf.readEoln();

    // No further input
    inf.readEof();
    return 0;
}
