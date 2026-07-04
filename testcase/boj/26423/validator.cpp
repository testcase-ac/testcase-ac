#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, 100000, "N");
        inf.readSpace();
        int m = inf.readInt(1, 100000, "M");
        inf.readSpace();
        inf.readInt(1, 20, "K");
        inf.readEoln();

        set<pair<int, int>> statements;
        for (int i = 0; i < m; ++i) {
            int a = inf.readInt(1, n, "A_i");
            inf.readSpace();
            int b = inf.readInt(1, n, "B_i");
            inf.readEoln();

            ensuref(a != b,
                    "case %d statement %d has equal A_i and B_i: %d",
                    tc, i + 1, a);
            ensuref(statements.insert({a, b}).second,
                    "case %d has duplicate statement at index %d: (%d, %d)",
                    tc, i + 1, a, b);
        }
    }

    inf.readEof();
    return 0;
}
