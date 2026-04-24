#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and T
    int N = inf.readInt(3, 100, "N");
    inf.readSpace();
    int T = inf.readInt(0, 1000000, "T");
    inf.readEoln();

    // Read the grass-eating times grid
    for (int i = 0; i < N; i++) {
        // Read exactly N integers in [0,100000]
        inf.readInts(N, 0, 100000, "g");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
