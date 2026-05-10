#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and t
    int N = inf.readInt(1, 300000, "N");
    inf.readSpace();
    int t = inf.readInt(1, 1000, "t");
    inf.readEoln();

    // Read tree positions and heights
    vector<long long> xs(N);
    for (int i = 0; i < N; i++) {
        xs[i] = inf.readLong(-1000000000LL, 1000000000LL, "x_i");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "h_i");
        inf.readEoln();
    }

    // Check that all x_i are distinct
    vector<long long> sorted_xs = xs;
    sort(sorted_xs.begin(), sorted_xs.end());
    for (int i = 1; i < N; i++) {
        ensuref(sorted_xs[i] != sorted_xs[i-1],
                "Duplicate x_i detected: %lld", sorted_xs[i]);
    }

    inf.readEof();
    return 0;
}
