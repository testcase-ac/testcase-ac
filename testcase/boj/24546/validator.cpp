#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first line: N, K, H, W, D
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 100000, "K");
    inf.readSpace();
    int H = inf.readInt(1, 100000, "H");
    inf.readSpace();
    int W = inf.readInt(1, 100000, "W");
    inf.readSpace();
    int D = inf.readInt(1, 100000, "D");
    inf.readEoln();

    // Read the N rides
    for (int i = 0; i < N; i++) {
        int h_lo = inf.readInt(1, 100000, "h_lo");
        inf.readSpace();
        int h_hi = inf.readInt(1, 100000, "h_hi");
        inf.readSpace();
        int w_lo = inf.readInt(1, 100000, "w_lo");
        inf.readSpace();
        int w_hi = inf.readInt(1, 100000, "w_hi");
        inf.readEoln();

        ensuref(h_lo <= h_hi,
                "h_lo > h_hi at ride %d: %d > %d", i+1, h_lo, h_hi);
        ensuref(w_lo <= w_hi,
                "w_lo > w_hi at ride %d: %d > %d", i+1, w_lo, w_hi);
    }

    inf.readEof();
    return 0;
}
