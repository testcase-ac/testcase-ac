#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 300000, "M");
    inf.readSpace();
    int k = inf.readInt(1, 10000, "K");
    inf.readEoln();

    set<int> profits;
    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "A_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "B_i");
        inf.readSpace();
        int c = inf.readInt(1, 1000000000, "C_i");
        inf.readEoln();

        // CHECK: The extracted limit line lost its comparison symbol; railway endpoints are interpreted as distinct cities.
        ensuref(a != b, "self-loop at railway %d: (%d, %d)", i, a, b);
        ensuref(profits.insert(c).second, "duplicate profit at railway %d: %d", i, c);
    }

    inf.readEof();
}
