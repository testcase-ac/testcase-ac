#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        // Number of nodes in this test
        int N = inf.readInt(2, 10000, "N");
        inf.readEoln();

        // Parent array: parent[i] = 0 means no parent assigned yet
        vector<int> parent(N+1, 0);
        // To detect duplicate edges
        set<pair<int,int>> edges;

        // Read N-1 edges
        for (int i = 0; i < N - 1; i++) {
            int A = inf.readInt(1, N, "A_i");
            inf.readSpace();
            int B = inf.readInt(1, N, "B_i");
            inf.readEoln();

            // No self-loop
            ensuref(A != B,
                    "Loop detected at edge %d: parent %d -> child %d", i+1, A, B);

            // No node has more than one parent
            ensuref(parent[B] == 0,
                    "Multiple parents detected for node %d: previous parent %d, new parent %d",
                    B, parent[B], A);

            // No duplicate edge
            ensuref(!edges.count({A,B}),
                    "Duplicate edge detected: %d -> %d", A, B);

            parent[B] = A;
            edges.insert({A,B});
        }

        // Exactly one root must exist
        int root_count = 0;
        for (int i = 1; i <= N; i++) {
            if (parent[i] == 0) root_count++;
        }
        ensuref(root_count == 1,
                "There must be exactly one root, but found %d roots", root_count);

        // Read the query nodes u and v
        int u = inf.readInt(1, N, "u");
        inf.readSpace();
        int v = inf.readInt(1, N, "v");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
