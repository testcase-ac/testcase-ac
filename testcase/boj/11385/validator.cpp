#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 1000000, "M");
    inf.readEoln();

    // Read f(x) coefficients: N+1 numbers, each in [1, 1000000]
    vector<int> a = inf.readInts(N + 1, 1, 1000000, "a_i");
    inf.readEoln();

    // Read g(x) coefficients: M+1 numbers, each in [1, 1000000]
    vector<int> b = inf.readInts(M + 1, 1, 1000000, "b_i");
    inf.readEoln();

    // No further input
    inf.readEof();
}
