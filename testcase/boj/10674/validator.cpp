#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The local legacy statement text is corrupted around this bound;
    // the original source statement gives 1 <= N <= 16.
    int n = inf.readInt(1, 16, "n");
    inf.readSpace();
    int maxM = n * (n - 1) / 2;
    int m = inf.readInt(0, maxM, "m");
    inf.readEoln();

    set<pair<int, int>> paths;
    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readSpace();
        int c = inf.readInt(1, 100, "c");
        inf.readSpace();
        int d = inf.readInt(1, 100, "d");
        inf.readEoln();

        ensuref(a < b, "path %d must satisfy a < b, found %d %d", i, a, b);
        ensuref(paths.insert({a, b}).second,
                "duplicate path between fields %d and %d", a, b);
    }

    inf.readEof();
}
