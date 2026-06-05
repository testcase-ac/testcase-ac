#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 20, "t");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 5000, "n");
        (void)n;
        inf.readSpace();
        int m = inf.readInt(1, 10, "m");
        inf.readEoln();

        set<int> scores;
        // CHECK: The Korean text says the next M lines contain S_i, but the English original and official sample put all M scores on one line.
        for (int i = 1; i <= m; ++i) {
            int score = inf.readInt(1, 20, "s_i");
            ensuref(scores.insert(score).second, "duplicate score value %d in test case %d", score, tc);

            if (i < m) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    inf.readEof();
}
