#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int t = 1; t <= T; ++t) {
        setTestCase(t);

        int N = inf.readInt(1, 20, "N");
        inf.readEoln();

        vector<int> p = inf.readInts(N, 1, N, "P_i");
        inf.readEoln();

        vector<bool> seen(N + 1, false);
        for (int i = 0; i < N; ++i) {
            ensuref(!seen[p[i]], "duplicate permutation value at position %d: %d", i + 1, p[i]);
            seen[p[i]] = true;
        }
    }

    inf.readEof();
}
