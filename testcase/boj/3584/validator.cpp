#include "testlib.h"
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int N = inf.readInt(2, 10000, "N");
        inf.readEoln();

        vector<int> parent(N+1, 0);
        set<pair<int,int>> edges;

        for (int i = 0; i < N - 1; i++) {
            int A = inf.readInt(1, N, "A_i");
            inf.readSpace();
            int B = inf.readInt(1, N, "B_i");
            inf.readEoln();

            ensuref(A != B,
                    "Loop detected at edge %d: parent %d -> child %d", i+1, A, B);

            ensuref(parent[B] == 0,
                    "Multiple parents detected for node %d: previous parent %d, new parent %d",
                    B, parent[B], A);

            ensuref(!edges.count({A,B}),
                    "Duplicate edge detected: %d -> %d", A, B);

            parent[B] = A;
            edges.insert({A,B});
        }

        int root = 0;
        int root_count = 0;
        for (int i = 1; i <= N; i++) {
            if (parent[i] == 0) {
                root = i;
                root_count++;
            }
        }
        ensuref(root_count == 1,
                "There must be exactly one root, but found %d roots", root_count);

        for (int node = 1; node <= N; ++node) {
            vector<int> seen(N + 1, 0);
            int current = node;
            while (current != 0) {
                ensuref(!seen[current],
                        "Cycle detected while following parents from node %d", node);
                seen[current] = 1;
                current = parent[current];
            }
            ensuref(seen[root],
                    "Node %d is not connected to the root %d", node, root);
        }

        int u = inf.readInt(1, N, "u");
        inf.readSpace();
        int v = inf.readInt(1, N, "v");
        inf.readEoln();
        ensuref(u != v, "Query nodes must be distinct, but both are %d", u);
    }

    inf.readEof();
    return 0;
}
