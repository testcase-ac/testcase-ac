#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, n, "M");
    inf.readEoln();

    vector<long long> k(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        k[i] = inf.readLong(1LL, 100000000LL, "K_i");
    }
    inf.readEoln();

    int r = inf.readInt(0, 100000, "R");
    inf.readEoln();

    set<pair<int, int>> relations;
    vector<long long> incomingReduction(n + 1, 0);
    for (int i = 1; i <= r; ++i) {
        int a = inf.readInt(1, n, "A");
        inf.readSpace();
        int b = inf.readInt(1, n, "B");
        inf.readSpace();
        int d = inf.readInt(1, 100000000, "D");
        inf.readEoln();

        ensuref(a != b, "self relation at index %d: %d -> %d", i, a, b);
        ensuref(relations.insert({a, b}).second,
                "duplicate relation at index %d: %d -> %d", i, a, b);

        incomingReduction[b] += d;
    }

    for (int i = 1; i <= n; ++i) {
        ensuref(k[i] - incomingReduction[i] > 0,
                "algorithm %d can be reduced to non-positive study amount", i);
    }

    inf.readEof();
}
