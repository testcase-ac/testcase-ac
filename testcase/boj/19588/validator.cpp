#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, n, "m");
    inf.readEoln();

    set<int> skills;
    for (int i = 1; i <= n; ++i) {
        int x = inf.readInt(1, 1000000000, "x");
        inf.readSpace();
        inf.readInt(1, 1000000000, "y");
        inf.readEoln();

        ensuref(skills.insert(x).second, "duplicate skill x at member %d: %d", i, x);
    }

    int q = inf.readInt(1, 500000, "q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(0, n - 1, "b_i");
        inf.readEoln();

        setTestCase(i);
        ensuref(1LL * m * a + b <= n,
                "query %d cannot choose M*a candidates after excluding b members: M=%d, a=%d, b=%d, n=%d",
                i, m, a, b, n);
    }

    inf.readEof();
}
