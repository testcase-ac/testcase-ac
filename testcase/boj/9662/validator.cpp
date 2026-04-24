#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read M: 1 ≤ M ≤ 10^9
    long long M = inf.readLong(1LL, 1000000000LL, "M");
    inf.readEoln();

    // Read K: number of allowed moves, 1 ≤ K ≤ 22
    int K = inf.readInt(1, 22, "K");
    inf.readEoln();

    // Read the K allowed move sizes a_i: each 1 ≤ a_i ≤ 22, strictly increasing, no duplicates
    vector<int> a(K);
    for (int i = 0; i < K; i++) {
        a[i] = inf.readInt(1, 22, "a_i");
        if (i + 1 < K) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }
    // Check strict ascending order (no duplicates, sorted)
    for (int i = 1; i < K; i++) {
        ensuref(a[i] > a[i - 1],
                "a_i must be strictly increasing: a[%d]=%d, a[%d]=%d",
                i-1, a[i-1], i, a[i]);
    }

    inf.readEof();
    return 0;
}
