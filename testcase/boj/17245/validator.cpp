#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Read the N x N grid of server counts
    for (int i = 0; i < N; i++) {
        // Each row has exactly N integers between 0 and 1e7
        inf.readInts(N, 0, 10000000, "h");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
