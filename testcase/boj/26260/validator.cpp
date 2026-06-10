#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 131071, "N");
    inf.readEoln();

    int nodes = 1;
    bool validSize = false;
    for (int k = 2; k <= 17; ++k) {
        nodes = nodes * 2 + 1;
        if (n == nodes) {
            validSize = true;
        }
    }
    ensuref(validSize, "N must be 2^k - 1 for 2 <= k <= 17, got %d", n);

    vector<long long> a(n + 1);
    set<long long> visible;
    int hiddenIndex = -1;
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        a[i] = inf.readLong(-1LL, 1000000000LL, "A_i");
        if (a[i] == -1) {
            ensuref(hiddenIndex == -1, "more than one hidden node");
            hiddenIndex = i;
        } else {
            ensuref(visible.insert(a[i]).second, "duplicate visible value %lld", a[i]);
        }
    }
    inf.readEoln();

    ensuref(hiddenIndex != -1, "there must be exactly one hidden node");
    ensuref(hiddenIndex * 2 > n, "hidden node must be a leaf, got index %d", hiddenIndex);

    long long x = inf.readLong(0LL, 1000000000LL, "X");
    inf.readEoln();
    ensuref(!visible.count(x), "X must be distinct from visible A_i values: %lld", x);

    vector<long long> low(n + 1, -1);
    vector<long long> high(n + 1, 1000000001LL);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            int parent = i / 2;
            low[i] = low[parent];
            high[i] = high[parent];
            if (i % 2 == 0) {
                high[i] = min(high[i], a[parent]);
            } else {
                low[i] = max(low[i], a[parent]);
            }
        }

        if (a[i] != -1) {
            ensuref(low[i] < a[i] && a[i] < high[i],
                    "node %d value %lld violates BST bounds (%lld, %lld)",
                    i, a[i], low[i], high[i]);
        }
    }

    long long hiddenLow = max(0LL, low[hiddenIndex] + 1);
    long long hiddenHigh = min(1000000000LL, high[hiddenIndex] - 1);
    ensuref(hiddenLow <= hiddenHigh,
            "hidden node %d has no value within BST bounds (%lld, %lld)",
            hiddenIndex, low[hiddenIndex], high[hiddenIndex]);

    long long candidate = hiddenLow;
    auto it = visible.lower_bound(candidate);
    while (candidate <= hiddenHigh && it != visible.end() && *it == candidate) {
        ++candidate;
        ++it;
    }
    ensuref(candidate <= hiddenHigh,
            "hidden node %d has no distinct value in [%lld, %lld]",
            hiddenIndex, hiddenLow, hiddenHigh);

    inf.readEof();
}
