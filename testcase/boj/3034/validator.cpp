#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, W, H
    int N = inf.readInt(1, 50, "N");
    inf.readSpace();
    int W = inf.readInt(1, 100, "W");
    inf.readSpace();
    int H = inf.readInt(1, 100, "H");
    inf.readEoln();

    // Each match length
    for (int i = 0; i < N; i++) {
        // length of the i-th match
        inf.readInt(1, 1000, "l_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
