#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int testCount = 0;
    while (true) {
        // Read N, M
        int N = inf.readInt(0, 500, "N");
        inf.readSpace();
        int M = inf.readInt(0, 10000, "M");
        inf.readEoln();

        // Termination condition
        if (N == 0 && M == 0)
            break;

        // Count test cases
        testCount++;
        ensuref(testCount <= 100000,
                "Number of test cases exceeds 100000: %d", testCount);

        // Validate N and M ranges
        ensuref(N >= 2,
                "N must be at least 2, found %d", N);
        ensuref(M >= 1,
                "M must be at least 1, found %d", M);

        // Read S, D
        int S = inf.readInt(0, N-1, "S");
        inf.readSpace();
        int D = inf.readInt(0, N-1, "D");
        inf.readEoln();
        ensuref(S != D,
                "S and D must differ: S=%d, D=%d", S, D);

        // Read edges, ensure no loops or duplicates
        set<pair<int,int>> edges;
        for (int i = 0; i < M; i++) {
            int U = inf.readInt(0, N-1, "U_i");
            inf.readSpace();
            int V = inf.readInt(0, N-1, "V_i");
            inf.readSpace();
            int P = inf.readInt(1, 1000, "P_i");
            inf.readEoln();

            ensuref(U != V,
                    "Loop detected at edge %d: U=%d, V=%d", i, U, V);
            pair<int,int> uv = make_pair(U, V);
            ensuref(!edges.count(uv),
                    "Multiple edges detected at edge %d: U=%d, V=%d", i, U, V);
            edges.insert(uv);
        }
    }

    inf.readEof();
    return 0;
}
