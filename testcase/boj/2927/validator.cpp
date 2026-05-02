#include "testlib.h"
#include <vector>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 30000, "N");
    inf.readEoln();

    // 2. Read penguin counts
    vector<int> penguins = inf.readInts(N, 0, 1000, "penguins");
    inf.readEoln();

    // 3. Read Q
    int Q = inf.readInt(1, 300000, "Q");
    inf.readEoln();

    // 4. Prepare for simulation
    set<pair<int,int>> bridges; // store (min(a,b), max(a,b)) for uniqueness

    for (int q = 0; q < Q; ++q) {
        string cmd = inf.readToken("[a-z]+", "command");
        if (cmd == "bridge") {
            inf.readSpace();
            int A = inf.readInt(1, N, "A");
            inf.readSpace();
            int B = inf.readInt(1, N, "B");
            inf.readEoln();

            ensuref(A != B, "bridge command at line %d: A (%d) and B (%d) must be different", q+4, A, B);

            int a = min(A, B), b = max(A, B);
            ensuref(!bridges.count({a, b}), "bridge command at line %d: duplicate bridge between %d and %d", q+4, a, b);

            bridges.insert({a, b});
        }
        else if (cmd == "penguins") {
            inf.readSpace();
            int A = inf.readInt(1, N, "A");
            inf.readSpace();
            int X = inf.readInt(0, 1000, "X");
            inf.readEoln();
            // No further validation needed
        }
        else if (cmd == "excursion") {
            inf.readSpace();
            int A = inf.readInt(1, N, "A");
            inf.readSpace();
            int B = inf.readInt(1, N, "B");
            inf.readEoln();
            // No further validation needed
        }
        else {
            ensuref(false, "Unknown command '%s' at line %d", cmd.c_str(), q+4);
        }
    }

    inf.readEof();
}
