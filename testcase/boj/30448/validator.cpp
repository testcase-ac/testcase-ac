#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read L and k
    long long L = inf.readLong(1LL, 1000000000LL, "L");
    inf.readSpace();
    int k = inf.readInt(1, 100000, "k");
    inf.readEoln();

    // Read c_1 ... c_k
    vector<long long> c = inf.readLongs(k, 0LL, 1000000LL, "c_i");
    inf.readEoln();

    // Read N
    int N = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    // Read the N input points
    vector<long long> xs, ys;
    xs.reserve(N);
    ys.reserve(N);
    vector<int> countP(k+1, 0);

    for (int t = 0; t < N; t++) {
        long long x = inf.readLong(0LL, L, "x");
        inf.readSpace();
        long long y = inf.readLong(0LL, L, "y");
        inf.readSpace();
        int idx = inf.readInt(1, k, "i");
        inf.readEoln();

        xs.push_back(x);
        ys.push_back(y);
        countP[idx]++;
    }

    // Check that no two points share the same x (no two on a vertical line)
    sort(xs.begin(), xs.end());
    for (int i = 1; i < N; i++) {
        ensuref(xs[i] != xs[i-1],
                "Axis-parallel line passes through two or more points: duplicate x = %lld",
                xs[i]);
    }

    // Check that no two points share the same y (no two on a horizontal line)
    sort(ys.begin(), ys.end());
    for (int i = 1; i < N; i++) {
        ensuref(ys[i] != ys[i-1],
                "Axis-parallel line passes through two or more points: duplicate y = %lld",
                ys[i]);
    }

    inf.readEof();
    return 0;
}
