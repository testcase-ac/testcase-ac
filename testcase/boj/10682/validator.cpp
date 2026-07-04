#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int decimalLength(int value) {
    int length = 1;
    while (value >= 10) {
        value /= 10;
        ++length;
    }
    return length;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxN = 100000;
    const int maxM = 100000;
    const int maxDatasets = 50;
    const long long maxInputBytes = 5LL * 1000 * 1000;

    int datasets = 0;
    long long inputBytes = 0;

    while (true) {
        int n = inf.readInt(0, maxN, "N");
        inf.readSpace();
        int m = inf.readInt(0, maxM, "M");
        inf.readEoln();
        inputBytes += decimalLength(n) + 1 + decimalLength(m) + 1;

        if (n == 0 && m == 0) {
            break;
        }

        ensuref(n >= 1, "N must be at least 1 before the terminating line");
        ++datasets;
        ensuref(datasets <= maxDatasets, "too many datasets: %d", datasets);

        set<pair<int, int>> specialPairs;
        for (int i = 0; i < m; ++i) {
            int a = inf.readInt(1, n, "a_i");
            inf.readSpace();
            int b = inf.readInt(1, n, "b_i");
            inf.readEoln();
            inputBytes += decimalLength(a) + 1 + decimalLength(b) + 1;

            ensuref(a < b, "special pair %d has a >= b: %d %d", i + 1, a, b);
            ensuref(specialPairs.insert({a, b}).second,
                    "duplicate special pair at index %d: %d %d", i + 1, a, b);
        }
    }

    // CHECK: The statement gives no lower bound for the dataset count; require
    // at least one real dataset so the input contains a problem instance.
    ensuref(datasets >= 1, "input must contain at least one dataset");
    ensuref(inputBytes < maxInputBytes, "input size must be less than 5 MB");

    inf.readEof();
}
