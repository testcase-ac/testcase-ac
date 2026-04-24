#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 300000, "N");
    inf.readSpace();
    int K = inf.readInt(1, N, "K");
    inf.readEoln();

    // Read the heights array
    vector<long long> h = inf.readLongs(N, 1LL, 1000000000LL, "h_i");
    inf.readEoln();

    // Check non-decreasing order
    for (int i = 1; i < N; i++) {
        ensuref(h[i-1] <= h[i],
                "Heights must be non-decreasing: h[%d]=%lld > h[%d]=%lld",
                i-1, h[i-1], i, h[i]);
    }

    inf.readEof();
    return 0;
}
