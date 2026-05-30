#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int instances = 0;
    while (true) {
        int p = inf.readInt(0, 10000, "P");
        inf.readSpace();

        long long maxConnections = 1LL * p * (p - 1) / 2;
        long long c = inf.readLong(0, maxConnections, "C");
        inf.readEoln();

        if (p == 0) {
            ensuref(c == 0, "only 0 0 may terminate the input");
            break;
        }

        ++instances;
        ensuref(instances <= 100000, "too many instances");

        set<pair<int, int>> seen;
        for (long long i = 0; i < c; ++i) {
            int p1 = inf.readInt(0, p - 1, "p1");
            inf.readSpace();
            int p2 = inf.readInt(0, p - 1, "p2");
            inf.readEoln();

            ensuref(p1 != p2, "loop at connection %lld: %d %d", i + 1, p1, p2);
            if (p1 > p2) {
                swap(p1, p2);
            }
            ensuref(seen.insert({p1, p2}).second,
                    "duplicate connection at connection %lld: %d %d", i + 1, p1, p2);
        }
    }

    inf.readEof();
}
