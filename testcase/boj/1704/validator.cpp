#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions M, N
    int M = inf.readInt(1, 15, "M");
    inf.readSpace();
    int N = inf.readInt(1, 15, "N");
    inf.readEoln();

    // Read grid of 0/1 values
    for (int i = 0; i < M; i++) {
        vector<int> row = inf.readInts(N, 0, 1, "cell");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
