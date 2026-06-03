#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(2, 99, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int N = inf.readInt(0, 20, "N");
        inf.readSpace();
        int M = inf.readInt(5, 20, "M");
        inf.readEoln();

        set<pair<int, int>> seen;
        for (int i = 1; i <= N; ++i) {
            int x = inf.readInt(0, M - 1, "x");
            inf.readSpace();
            int y = inf.readInt(0, M - 1, "y");
            inf.readSpace();
            inf.readInt(1, 4, "z");
            inf.readEoln();

            // CHECK: The statement describes a relationship between two politicians.
            ensuref(x != y, "relationship %d is a self-loop at politician %d", i, x);

            // CHECK: A pair of politicians has one relationship strength.
            pair<int, int> edge = minmax(x, y);
            ensuref(seen.insert(edge).second,
                    "duplicate relationship %d between politicians %d and %d", i, edge.first, edge.second);
        }
    }

    inf.readEof();
    return 0;
}
