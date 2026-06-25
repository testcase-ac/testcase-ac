#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int m = inf.readInt(0, n - 1, "m");
        inf.readSpace();
        inf.readInt(0, 1000, "t");
        inf.readEoln();

        for (int edge = 1; edge <= m; ++edge) {
            int s = inf.readInt(0, n - 1, "s");
            inf.readSpace();
            inf.readInt(1, n, "x");

            set<int> forbidden;
            for (int j = 1; j <= s; ++j) {
                inf.readSpace();
                int a = inf.readInt(1, n, "a_j");
                ensuref(a != i,
                        "forbidden predecessor a_%d for server %d must not equal i",
                        j, i);
                ensuref(forbidden.insert(a).second,
                        "duplicate forbidden predecessor %d for server %d edge %d",
                        a, i, edge);
            }
            inf.readEoln();
        }
    }

    inf.readEof();
}
