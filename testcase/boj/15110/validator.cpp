#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 5000, "m");
    inf.readSpace();
    long long k = inf.readLong(1LL, 1000000000LL, "k");
    inf.readEoln();

    int s = inf.readInt(1, n, "s");
    inf.readSpace();
    int t = inf.readInt(1, n, "t");
    ensuref(s != t, "s and t must be different: %d", s);
    inf.readEoln();

    set<pair<int, int>> doors;
    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readSpace();
        long long c = inf.readLong(1LL, k, "c_i");
        inf.readSpace();
        long long d = inf.readLong(c, k, "d_i");
        inf.readEoln();

        ensuref(a != b, "door %d has identical endpoints: %d", i, a);
        ensuref(doors.insert({a, b}).second,
                "duplicate directed door at index %d: %d -> %d", i, a, b);
    }

    inf.readEof();
}
