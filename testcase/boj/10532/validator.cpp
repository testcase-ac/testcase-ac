#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(2, 10000, "N");
    inf.readSpace();
    long long M = inf.readInt(1, 20000, "M");
    // M must also satisfy M ≤ N^2 - N
    long long maxEdges = (long long)N * N - N;
    ensuref(M <= maxEdges,
            "M must be ≤ N^2 - N; got M = %lld, N = %d (N^2 - N = %lld)",
            M, N, maxEdges);
    inf.readEoln();

    // Read M declarations of interest
    set<pair<int,int>> edges;
    for (int i = 0; i < M; i++) {
        int A = inf.readInt(0, N-1, "A_i");
        inf.readSpace();
        int B = inf.readInt(0, N-1, "B_i");
        inf.readEoln();

        // No self-loops
        ensuref(A != B,
                "Self-loop detected at declaration %d: (%d, %d)",
                i, A, B);
        // No duplicate edges
        pair<int,int> e = make_pair(A, B);
        ensuref(!edges.count(e),
                "Duplicate declaration detected at index %d: (%d, %d)",
                i, A, B);
        edges.insert(e);
    }

    inf.readEof();
    return 0;
}
