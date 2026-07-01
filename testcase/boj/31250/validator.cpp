#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long MAX_VALUE = 1000000000000000000LL;

    int n = inf.readInt(2, 500, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "M");
    inf.readSpace();
    inf.readLong(1LL, MAX_VALUE, "K");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        inf.readLong(0LL, MAX_VALUE, "A_i");
    }
    inf.readEoln();

    set<long long> seenB;
    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readSpace();
        long long b = inf.readLong(0LL, MAX_VALUE, "B_i");
        inf.readEoln();

        ensuref(u != v, "edge %d is a self-loop: %d -> %d", i, u, v);
        ensuref(seenB.insert(b).second, "duplicate B_i at edge %d: %lld", i, b);
    }

    inf.readEof();
    return 0;
}
