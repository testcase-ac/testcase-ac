#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(6, 10, "N");
    inf.readEoln();

    // Read the grid of prices
    for (int i = 0; i < N; i++) {
        // Each row has exactly N integers in [0,200]
        inf.readInts(N, 0, 200, "G");
        inf.readEoln();
    }

    // No extra content
    inf.readEof();
    return 0;
}
