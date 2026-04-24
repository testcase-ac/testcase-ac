#include "testlib.h"
#include <vector>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 50, "N");
    inf.readEoln();

    // Read block heights
    vector<long long> h = inf.readLongs(N, 1LL, 500000LL, "h_i");
    inf.readEoln();

    // Check total sum constraint
    long long total = 0;
    for (int i = 0; i < N; i++) {
        total += h[i];
        // Overflow is impossible since N <= 50 and each h[i] <= 500000
    }
    ensuref(total <= 500000LL,
            "Sum of heights must be at most 500000, but got %lld",
            total);

    inf.readEof();
    return 0;
}
