#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read M, N, K
        int M = inf.readInt(1, 50, "M");
        inf.readSpace();
        int N = inf.readInt(1, 50, "N");
        inf.readSpace();
        int K = inf.readInt(1, 2500, "K");
        inf.readEoln();

        // Track positions to ensure no duplicates
        set<pair<int,int>> pos;
        pos.clear();

        for (int i = 0; i < K; i++) {
            int X = inf.readInt(0, M - 1, "X");
            inf.readSpace();
            int Y = inf.readInt(0, N - 1, "Y");
            inf.readEoln();

            pair<int,int> p = make_pair(X, Y);
            ensuref(!pos.count(p),
                    "Duplicate cabbage position in case %d at index %d: (%d, %d)",
                    tc, i, X, Y);
            pos.insert(p);
        }
    }

    inf.readEof();
    return 0;
}
