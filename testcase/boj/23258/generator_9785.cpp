#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

struct Query {
    int C, s, e;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3); // 0,1,2,3 -> 4 modes

    int N;
    vector<vector<int>> D;
    vector<Query> qs;

    auto initMatrix = [&](int n) {
        N = n;
        D.assign(N + 1, vector<int>(N + 1, 0));
    };

    auto addEdge = [&](int u, int v, int w) {
        if (u == v) return;
        D[u][v] = D[v][u] = w;
    };

    if (mode == 0) {
        // Small line graph, random size, to test basic behavior and some dewblocking
        int n = rnd.next(3, 6);
        initMatrix(n);

        for (int i = 1; i < N; ++i) {
            int w = rnd.next(1, 20);
            addEdge(i, i + 1, w);
        }

        int Q = rnd.next(4, 10);

        // Some fixed-pattern queries

        // 1) Very strict C, likely impossible except for neighbors
        qs.push_back({1, 1, N});           // typically impossible
        // 2) Very loose C, effectively ignore dew
        qs.push_back({N + 1, 1, N});
        // 3) s = e
        int x = rnd.next(1, N);
        qs.push_back({rnd.next(1, N + 1), x, x});

        // 4) boundary C around interior node indexes
        if (N >= 4) {
            // path 1 -> 4 has interior {2,3}, max=3
            // C=3 should forbid, C=4 should allow
            qs.push_back({3, 1, 4});
            qs.push_back({4, 1, 4});
        }

        while ((int)qs.size() < Q) {
            Query q;
            q.C = rnd.next(1, N + 1);
            if (rnd.next(0, 3) == 0) {
                // s = e case
                q.s = q.e = rnd.next(1, N);
            } else {
                q.s = rnd.next(1, N);
                q.e = rnd.next(1, N);
            }
            qs.push_back(q);
        }

    } else if (mode == 1) {
        // Structured graph with multiple alternative paths and subtle dew constraints
        initMatrix(6);

        // Edges:
        // 1-2-3-4 path with small weights
        addEdge(1, 2, 2);
        addEdge(2, 3, 2);
        addEdge(3, 4, 2);
        // direct but slower
        addEdge(1, 4, 10);
        // another path 1-5-4
        addEdge(1, 5, 3);
        addEdge(5, 4, 3);
        // another path 1-2-6-4
        addEdge(2, 6, 1);
        addEdge(6, 4, 1);

        // Core queries focusing on 1 -> 4 with various C
        qs.push_back({1, 1, 4}); // only direct 1-4 valid
        qs.push_back({3, 1, 4}); // forbid via node 3, allow via 5 or 6 depending on C
        qs.push_back({4, 1, 4}); // now path 1-2-3-4 allowed
        qs.push_back({5, 1, 4}); // still forbid through node 5 (index 5)
        qs.push_back({6, 1, 4}); // allow through 5 as interior max=5<6
        qs.push_back({7, 1, 4}); // N+1, all allowed

        // Dew constraints on a smaller path: 1-2-3
        qs.push_back({2, 1, 3}); // interior {2}, 2^2 == 2^2 -> sum >= 2^C, so forbidden
        qs.push_back({3, 1, 3}); // now allowed

        // Endpoint with large index but allowed as endpoint
        // Path 6-2-1 (interior {2}) for C=3 is allowed
        qs.push_back({3, 6, 1});

        // s = e case
        qs.push_back({2, 5, 5});

        // A couple random extras
        int extraQ = rnd.next(0, 3);
        while (extraQ--) {
            Query q;
            q.C = rnd.next(1, N + 1);
            if (rnd.next(0, 3) == 0) {
                q.s = q.e = rnd.next(1, N);
            } else {
                q.s = rnd.next(1, N);
                q.e = rnd.next(1, N);
            }
            qs.push_back(q);
        }

    } else if (mode == 2) {
        // Disconnected graph to enforce -1 answers plus dew constraints
        initMatrix(5);

        // Component 1: 1-2-3
        addEdge(1, 2, 3);
        addEdge(2, 3, 4);
        // Component 2: 4-5
        addEdge(4, 5, 5);

        // Dew-constrained and disconnected queries
        qs.push_back({1, 1, 3}); // should be impossible due to dew (interior=2)
        qs.push_back({3, 1, 3}); // now allowed (interior max=2<3)

        // Within second component
        qs.push_back({2, 4, 5}); // direct edge, always allowed

        // Cross components: impossible regardless of C
        qs.push_back({1, 1, 4});
        qs.push_back({4, 2, 5});

        // s = e
        qs.push_back({2, 4, 4});

        int extraQ = rnd.next(0, 3);
        while (extraQ--) {
            Query q;
            q.C = rnd.next(1, N + 1);
            if (rnd.next(0, 3) == 0) {
                q.s = q.e = rnd.next(1, N);
            } else {
                q.s = rnd.next(1, N);
                q.e = rnd.next(1, N);
            }
            qs.push_back(q);
        }

    } else {
        // Dense random graph, small N, to test general correctness
        int n = rnd.next(4, 7);
        initMatrix(n);

        // For density, connect all pairs with some positive weight
        for (int i = 1; i <= N; ++i) {
            for (int j = i + 1; j <= N; ++j) {
                int w = rnd.next(1, 30);
                addEdge(i, j, w);
            }
        }

        int Q = rnd.next(6, 15);

        // Specific boundary queries
        qs.push_back({1, 1, N});       // needs path with no interior nodes
        qs.push_back({N + 1, 1, N});   // no dew restriction
        qs.push_back({2, 1, 2});       // direct neighbor, always OK
        // C just below a middle node index for longer path
        if (N >= 4) {
            // interior of any path 1->4 in dense graph might include high index,
            // but algorithm must handle it.
            qs.push_back({3, 1, 4});
            qs.push_back({4, 1, 4});
        }

        while ((int)qs.size() < Q) {
            Query q;
            q.C = rnd.next(1, N + 1);
            if (rnd.next(0, 4) == 0) {
                q.s = q.e = rnd.next(1, N);
            } else {
                q.s = rnd.next(1, N);
                q.e = rnd.next(1, N);
            }
            qs.push_back(q);
        }
    }

    int Q = (int)qs.size();

    println(N, Q);
    for (int i = 1; i <= N; ++i) {
        vector<int> row;
        row.reserve(N);
        for (int j = 1; j <= N; ++j) {
            row.push_back(D[i][j]);
        }
        println(row);
    }
    for (const auto &q : qs) {
        println(q.C, q.s, q.e);
    }

    return 0;
}
