#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long a = inf.readLong(1LL, 1000000000LL, "A");
    inf.readSpace();
    long long b = inf.readLong(1LL, 1000000000LL, "B");
    inf.readSpace();
    int n = inf.readInt(0, 2000, "n");
    inf.readSpace();
    int m = inf.readInt(0, 2000, "m");
    inf.readEoln();

    set<long long> vertical;
    for (int i = 1; i <= n; ++i) {
        long long x = inf.readLong(1LL, a - 1, "a_i");
        inf.readEoln();
        ensuref(vertical.insert(x).second,
                "duplicate vertical fence coordinate at index %d: %lld", i, x);
    }

    set<long long> horizontal;
    for (int i = 1; i <= m; ++i) {
        long long y = inf.readLong(1LL, b - 1, "b_i");
        inf.readEoln();
        ensuref(horizontal.insert(y).second,
                "duplicate horizontal fence coordinate at index %d: %lld", i, y);
    }

    inf.readEof();
}
