#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read H, W, N
    int H = inf.readInt(1, 1000, "H");
    inf.readSpace();
    int W = inf.readInt(1, 1000, "W");
    inf.readSpace();
    int N = inf.readInt(1, 10000000, "N");
    inf.readEoln();

    // Read the grid of H rows and W columns with values 0 or 1
    for (int i = 0; i < H; i++) {
        inf.readInts(W, 0, 1, "c");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
