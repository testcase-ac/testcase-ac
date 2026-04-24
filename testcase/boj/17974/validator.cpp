#include "testlib.h"
#include <vector>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read m and n
    int m = inf.readInt(1, 100000, "m");
    inf.readSpace();
    int n = inf.readInt(1, 100000, "n");
    ensuref(m <= n, "m must be <= n, but m=%d, n=%d", m, n);
    inf.readEoln();

    // Read coordinates x[0..n-1]
    vector<ll> x = inf.readLongs(n, 0LL, 1000000000LL, "x_i");
    inf.readEoln();

    // Read colors c[0..n-1]
    vector<int> c = inf.readInts(n, 1, m, "c_i");
    inf.readEoln();

    // Check that coordinates are strictly increasing
    for (int i = 1; i < n; i++) {
        ensuref(x[i] > x[i-1],
                "Coordinates must be strictly increasing: x[%d-1]=%lld >= x[%d]=%lld",
                i, x[i-1], i, x[i]);
    }

    inf.readEof();
    return 0;
}
