#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and C
    int N = inf.readInt(2, 200000, "N");
    inf.readSpace();
    int C = inf.readInt(2, N, "C");
    inf.readEoln();

    // Read coordinates
    vector<long long> x(N);
    for (int i = 0; i < N; i++) {
        x[i] = inf.readLong(0LL, 1000000000LL, "x_i");
        inf.readEoln();
    }

    // Check for duplicate coordinates
    sort(x.begin(), x.end());
    for (int i = 1; i < N; i++) {
        ensuref(x[i] != x[i-1],
                "Duplicate x-coordinate at positions %d and %d: %lld",
                i, i+1, x[i]);
    }

    inf.readEof();
    return 0;
}
