#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(2, 5000, "N");
    inf.readEoln();

    // Read the sequence A of length N
    vector<int> A = inf.readInts(N, 1, 1000000, "A_i");
    inf.readEoln();

    // No further input
    inf.readEof();

    return 0;
}
