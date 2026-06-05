#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200000, "N");
    inf.readSpace();
    int m = inf.readInt(1, n - 1, "M");
    inf.readSpace();
    int k = inf.readInt(1, n - 1, "K");
    inf.readEoln();

    ensuref(m + k <= n, "M + K must be at most N: %d + %d > %d", m, k, n);

    set<int> hostScores;
    set<int> judgeScores;
    for (int i = 1; i <= n; ++i) {
        int a = inf.readInt(0, 1000000000, "a_i");
        inf.readSpace();
        int b = inf.readInt(0, 1000000000, "b_i");
        inf.readEoln();

        ensuref(hostScores.insert(a).second,
                "duplicate host score at student %d: %d", i, a);
        ensuref(judgeScores.insert(b).second,
                "duplicate judge score at student %d: %d", i, b);
    }

    inf.readEof();
    return 0;
}
