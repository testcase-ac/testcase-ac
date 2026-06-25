#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    long long b = inf.readLong(1LL, 1000000000LL, "B");
    inf.readEoln();

    set<long long> positions;
    for (int i = 1; i <= n; ++i) {
        long long size = inf.readLong(1LL, 1000000000LL, "S_j");
        inf.readSpace();
        long long position = inf.readLong(1LL, 1000000000LL, "P_j");
        inf.readEoln();

        ensuref(position != b, "bale %d is at Bessie's position %lld", i, b);
        ensuref(positions.insert(position).second,
                "duplicate bale position at bale %d: %lld", i, position);
        (void)size;
    }

    inf.readEof();
}
