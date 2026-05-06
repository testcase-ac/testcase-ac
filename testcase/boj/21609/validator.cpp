#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read grid size N and number of colors M
    int N = inf.readInt(1, 20, "N");
    inf.readSpace();
    int M = inf.readInt(1, 5, "M");
    inf.readEoln();

    // Read the N x N grid
    // Each cell must be -1 (black), 0 (rainbow), or 1..M (normal colors)
    for (int i = 1; i <= N; i++) {
        // Read exactly N integers in [-1, M]
        inf.readInts(N, -1, M, "grid");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
