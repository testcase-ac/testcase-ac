#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N and M
    int N = inf.readInt(1, 200, "N");
    inf.readSpace();
    int M = inf.readInt(1, 400, "M");
    inf.readEoln();

    // 2. Read t_i for each item
    vector<int> t(N+1); // 1-based
    for (int i = 1; i <= N; ++i) {
        t[i] = inf.readInt(-100000, 100000, "t_i");
        if (i < N) inf.readEoln();
        else inf.readEoln();
    }

    // 3. Read M relations, check for valid indices, and no self-dependency
    set<pair<int,int>> rels;
    for (int i = 0; i < M; ++i) {
        int s = inf.readInt(1, N, "s_i");
        inf.readSpace();
        int e = inf.readInt(1, N, "e_i");
        inf.readEoln();
        ensuref(s != e, "Self-dependency detected at relation %d: (%d, %d)", i+1, s, e);
        ensuref(!rels.count({s, e}), "Duplicate dependency detected at relation %d: (%d, %d)", i+1, s, e);
        rels.insert({s, e});
    }

    // 4. Check for cycles and build SCCs (for global property)
    // The problem allows cycles, but only in the sense that items in a cycle must be taken together or not at all.
    // So, we must check that the dependency graph is valid (no invalid indices, which is already checked).
    // No further global property is required for the input, as cycles are allowed.

    // 5. Check for formatting: EOF
    inf.readEof();
}
