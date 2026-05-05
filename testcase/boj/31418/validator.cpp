#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read W, H, K, T
    int W = inf.readInt(1, 1000000, "W");
    inf.readSpace();
    int H = inf.readInt(1, 1000000, "H");
    inf.readSpace();
    int K = inf.readInt(1, 1000000, "K");
    inf.readSpace();
    int T = inf.readInt(0, 1000000, "T");
    inf.readEoln();

    // Read K lines of (x_i, y_i)
    // All positions must be in [1,W] x [1,H]
    // No further constraints (positions can overlap, all positions allowed)
    for (int i = 0; i < K; ++i) {
        int x = inf.readInt(1, W, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, H, "y_i");
        inf.readEoln();
    }

    inf.readEof();
}
