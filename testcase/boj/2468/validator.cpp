#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: size of the grid
    int N = inf.readInt(2, 100, "N");
    inf.readEoln();

    // Read N rows of N heights each
    for (int i = 0; i < N; i++) {
        // Each height is a natural number between 1 and 100
        inf.readInts(N, 1, 100, "height");
        inf.readEoln();
    }

    // No extra characters after the grid
    inf.readEof();
    return 0;
}
