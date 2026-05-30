#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; tc++) {
        setTestCase(tc+1);

        int n = inf.readInt(2, 200, "n");
        inf.readSpace();
        int m = inf.readInt(1, n * (n - 1) / 2, "m");
        inf.readSpace();
        int start = inf.readInt(1, n, "start");
        inf.readSpace();
        int end = inf.readInt(1, n, "end");
        ensuref(start != end,
                "In test case %d: start (%d) and end (%d) must be different",
                tc+1, start, end);
        inf.readSpace();
        int s = inf.readInt(1, 1000, "s");
        inf.readSpace();
        int p = inf.readInt(1, 1000, "p");
        inf.readSpace();
        inf.readInt(s + 1, 1000, "y");
        inf.readEoln();

        set<pair<int,int>> seen;
        for (int i = 0; i < m; i++) {
            int a = inf.readInt(1, n, "a_i");
            inf.readSpace();
            int b = inf.readInt(1, n, "b_i");
            inf.readSpace();
            int c = inf.readInt(0, 100, "c_i");
            inf.readSpace();
            int d = inf.readInt(1, 1000, "d_i");
            inf.readEoln();

            ensuref(a < b,
                    "In test case %d, edge %d: a_i (%d) must be < b_i (%d)",
                    tc+1, i+1, a, b);
            pair<int,int> e = {a, b};
            ensuref(!seen.count(e),
                    "In test case %d, duplicate edge detected: (%d, %d)",
                    tc+1, a, b);
            seen.insert(e);
        }
    }

    inf.readEof();
    return 0;
}
