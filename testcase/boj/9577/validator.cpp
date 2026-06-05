#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    long long scalarTokens = 1;
    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 100, "n");
        inf.readSpace();
        int m = inf.readInt(1, 100, "m");
        inf.readEoln();
        scalarTokens += 2;

        for (int i = 1; i <= m; ++i) {
            int t1 = inf.readInt(0, 100, "t_1");
            inf.readSpace();
            int t2 = inf.readInt(t1, 100, "t_2");
            inf.readSpace();
            int a = inf.readInt(0, n, "a");
            scalarTokens += 3;

            set<int> pieces;
            for (int j = 1; j <= a; ++j) {
                inf.readSpace();
                int q = inf.readInt(1, n, "q_i");
                ensuref(pieces.insert(q).second,
                        "duplicate piece number in test case %d seed %d: %d",
                        tc, i, q);
                ++scalarTokens;
            }
            inf.readEoln();

            // CHECK: T has no statement bound; reject impractically huge numeric inputs.
            ensuref(scalarTokens <= 5000000,
                    "too many scalar tokens across all test cases: %lld",
                    scalarTokens);
        }
    }

    inf.readEof();
}
