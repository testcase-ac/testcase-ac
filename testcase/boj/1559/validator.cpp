#include "testlib.h"
#include <set>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int testcases = 0;
    while (true) {
        // Read M and N (or termination 0 0)
        int M = inf.readInt(0, 100, "M");
        inf.readSpace();
        int N = inf.readInt(0, 100, "N");
        inf.readEoln();
        // Termination condition
        if (M == 0 && N == 0) {
            break;
        }
        // Count test cases
        testcases++;
        ensuref(testcases <= 100000,
                "Number of test cases exceeds 100000 (at least %d)", testcases);
        // Validate M, N ranges
        ensuref(2 <= M && M <= 100 && 2 <= N && N <= 100,
                "M and N must both be zero for termination or 2 <= M,N <= 100; got M=%d, N=%d", M, N);

        // Read the maze rows
        string row_regex = "[NESW]{" + to_string(N) + "," + to_string(N) + "}";
        for (int i = 0; i < M; i++) {
            inf.readToken(row_regex, "row");
            inf.readEoln();
        }

        // Read number of treasures
        int K = inf.readInt(1, 8, "K");
        inf.readEoln();
        // Read treasure positions, no duplicates, not at (1,1) or (M,N)
        set<pair<int,int>> treasures;
        for (int i = 0; i < K; i++) {
            int r = inf.readInt(1, M, "r_i");
            inf.readSpace();
            int c = inf.readInt(1, N, "c_i");
            inf.readEoln();
            ensuref(!(r == 1 && c == 1),
                    "Treasure %d at forbidden start cell (1,1)", i+1);
            ensuref(!(r == M && c == N),
                    "Treasure %d at forbidden end cell (%d,%d)", i+1, M, N);
            pair<int,int> p = make_pair(r, c);
            ensuref(!treasures.count(p),
                    "Duplicate treasure position at index %d: (%d,%d)", i+1, r, c);
            treasures.insert(p);
        }
    }

    inf.readEof();
    return 0;
}
