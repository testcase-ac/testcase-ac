#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and Q
    int N = inf.readInt(1, 250000, "N");
    inf.readSpace();
    int Q = inf.readInt(1, 250000, "Q");
    inf.readEoln();

    // Read the array a[1..N]
    vector<long long> a = inf.readLongs(N, 1LL, 1000000000LL, "a");
    inf.readEoln();
    // Check non-increasing
    for (int i = 0; i + 1 < N; i++) {
        ensuref(a[i] >= a[i+1],
                "Array a must be non-increasing: a[%d]=%lld < a[%d]=%lld",
                i+1, a[i], i+2, a[i+1]);
    }

    // Read Q queries
    for (int i = 0; i < Q; i++) {
        inf.readInt(1, 1000000000, "x_i");
        inf.readSpace();
        inf.readInt(1, N, "y_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
