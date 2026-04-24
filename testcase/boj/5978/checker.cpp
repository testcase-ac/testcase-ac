#include "testlib.h"
#include <vector>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    // Read input graph
    int N = inf.readInt();            // number of towns
    int M = inf.readInt();            // number of paths
    vector<pair<int,int>> edges(M+1);
    for (int i = 1; i <= M; i++) {
        int a = inf.readInt(1, N);
        int b = inf.readInt(1, N);
        edges[i] = make_pair(a, b);
    }

    // Read jury answer: either -1 or a valid solution of size j_k
    int j_k = ans.readInt();
    if (j_k != -1) {
        // skip the jury's list of edges; validate indices in [1..M]
        for (int i = 0; i < j_k; i++)
            ans.readInt(1, M);
    }

    // Read participant answer
    if (ouf.eof())
        quitf(_pe, "participant output is empty");
    int p_k = ouf.readInt(-1, M, "number of paths to keep");

    // Case: jury says no solution
    if (j_k == -1) {
        if (p_k != -1)
            quitf(_wa, "expected -1 (no solution), found %d", p_k);
        quitf(_ok, "no solution as per jury");
    }

    // Now jury has a solution, so participant must not output -1
    if (p_k == -1)
        quitf(_wa, "participant says -1 but a solution exists");

    // Read participant's chosen edges and validate
    vector<bool> used_edge(M+1, false);
    vector<int> degree(N+1, 0);
    for (int i = 0; i < p_k; i++) {
        int idx = ouf.readInt(1, M, format("path[%d] index", i+1).c_str());
        if (used_edge[idx])
            quitf(_wa, "path %d is used more than once", idx);
        used_edge[idx] = true;
        degree[edges[idx].first]++;
        degree[edges[idx].second]++;
    }
    // Ensure no extra tokens
    ouf.readEof();

    // Check that each town has an odd degree
    for (int v = 1; v <= N; v++) {
        if (degree[v] % 2 == 0)
            quitf(_wa, "town %d has even degree %d", v, degree[v]);
    }

    // All checks passed
    quitf(_ok, "valid solution");
    return 0;
}
