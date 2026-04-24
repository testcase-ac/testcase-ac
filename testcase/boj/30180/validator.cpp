#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read header: H, W, N
    int H = inf.readInt(1, 500000, "H");
    inf.readSpace();
    int W = inf.readInt(1, 500000, "W");
    inf.readSpace();
    long long N = inf.readLong(1LL, 500000LL, "N");
    inf.readEoln();

    // Validate product constraint HW <= 500000
    long long HW = (long long)H * W;
    ensuref(HW <= 500000LL,
            "Product H*W must be <= 500000, but H=%d, W=%d gives %lld",
            H, W, HW);

    // Validate N <= HW
    ensuref(N <= HW,
            "N must be <= H*W, but N=%lld, H*W=%lld",
            N, HW);

    // Read the grid of sweetness values
    for (int i = 1; i <= H; i++) {
        for (int j = 1; j <= W; j++) {
            long long s = inf.readLong(1LL, 1000000000LL, "S");
            if (j < W)
                inf.readSpace();
        }
        inf.readEoln();
    }

    // No extra content
    inf.readEof();

    return 0;
}
