#include "testlib.h"
#include <vector>
#include <queue>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXN = 100000;
    const int MAXE = 100000;

    int N = inf.readInt(1, MAXN, "N");
    inf.readSpace();
    int E = inf.readInt(1, MAXE, "E");
    inf.readEoln();

    // Read edges, check basic constraints: 1-based, no loops, no multiple edges.
    vector<pair<int,int>> edges(E);
    set<pair<int,int>> edgeSet;
    vector<vector<int>> adj(N + 1);

    for (int i = 0; i < E; ++i) {
        int A = inf.readInt(1, N, "A_i");
        inf.readSpace();
        int B = inf.readInt(1, N, "B_i");
        inf.readEoln();

        ensuref(A != B, "Self-loop found at edge %d: (%d, %d)", i + 1, A, B);
        int u = A, v = B;
        if (u > v) swap(u, v);
        ensuref(!edgeSet.count({u, v}),
                "Multiple edge between %d and %d at input edge index %d", u, v, i + 1);
        edgeSet.insert({u, v});

        edges[i] = {A, B};
        adj[A].push_back(B);
        adj[B].push_back(A);
    }

    // Global property implied by the problem:
    // For any city with degree >= 2, its incident edges must be able to receive
    // at least one restaurant of each chain (1 and 2). This is equivalent to
    // requiring that for every connected component that contains a vertex of
    // degree >= 2, the edges can be 2-colored so that no vertex of degree >= 2
    // is incident only to one color.
    //
    // This is not guaranteed by arbitrary inputs; we must ensure that for the
    // given test data, a valid assignment always exists OR explicitly allow
    // impossible cases (where answer 0 is valid). The statement says: "If it's
    // impossible, print 0." Thus, there is NO guarantee that input always
    // admits a valid assignment, so we do NOT enforce existence of a solution.
    //
    // Hence no extra global feasibility check is required beyond graph-format
    // constraints.

    inf.readEof();
}
