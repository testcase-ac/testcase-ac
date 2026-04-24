#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(2, 10000, "n");
    inf.readEoln();

    // Read stone weights a[1..n]
    vector<int> a = inf.readInts(n, 1, 10000000, "a_i");
    inf.readEoln();

    // Sum constraint: total weight ≤ 10,000,000
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    ensuref(sum <= 10000000LL,
            "Sum of weights must be ≤ 10000000, but got %lld", sum);

    // No more data
    inf.readEof();
    return 0;
}
