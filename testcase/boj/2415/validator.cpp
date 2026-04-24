#include "testlib.h"
#include <set>
#include <utility>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(4, 1500, "N");
    inf.readEoln();

    // Read points and check for duplicates
    set<pair<long long, long long>> pts;
    for (int i = 0; i < N; i++) {
        char namex[32], namey[32];
        snprintf(namex, sizeof(namex), "x[%d]", i);
        snprintf(namey, sizeof(namey), "y[%d]", i);

        long long x = inf.readLong(-100000000LL, 100000000LL, namex);
        inf.readSpace();
        long long y = inf.readLong(-100000000LL, 100000000LL, namey);
        inf.readEoln();

        pair<long long,long long> p = make_pair(x, y);
        ensuref(!pts.count(p),
                "Duplicate point at index %d: (%lld, %lld)", i, x, y);
        pts.insert(p);
    }

    inf.readEof();
    return 0;
}
