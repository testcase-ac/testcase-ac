#include "testlib.h"
#include <vector>
#include <algorithm>
#include <array>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // 1. Hyper-parameter: number of nodes
    int N = rnd.next(2, 10);

    // 2. Hyper-parameter: tree shape type
    //    0 = random tree, 1 = chain, 2 = star
    int treeType = rnd.next(0, 2);

    // Build the tree edges (u,v) without weights yet
    vector<array<int,3>> edges; // {u, v, w}
    if (treeType == 1) {
        // chain
        for (int i = 2; i <= N; i++) {
            edges.push_back({i-1, i, 0});
        }
    } else if (treeType == 2) {
        // star
        int center = rnd.next(1, N);
        for (int i = 1; i <= N; i++) {
            if (i == center) continue;
            edges.push_back({center, i, 0});
        }
    } else {
        // random tree via Prüfer-like
        // connect each i to a random previous node
        for (int i = 2; i <= N; i++) {
            int p = rnd.next(1, i-1);
            edges.push_back({p, i, 0});
        }
    }

    // 3. Hyper-parameter: maximum initial weight
    int maxW = rnd.next(1, 1000);
    for (auto &e : edges) {
        e[2] = rnd.next(1, maxW);
    }

    // 4. Hyper-parameter: shuffle edge order with 50% chance
    if (rnd.next(0, 1) == 1) {
        shuffle(edges.begin(), edges.end());
    }

    // 5. Queries
    int M = rnd.next(1, 20);
    double pUpd = rnd.next(0.0, 1.0); // probability of update
    vector<array<int,3>> queries;
    int cntType2 = 0;
    for (int i = 0; i < M; i++) {
        if (rnd.next() < pUpd) {
            // type 1 query: update edge cost
            int eid = rnd.next(1, N-1);
            int c = rnd.next(1, maxW);
            queries.push_back({1, eid, c});
        } else {
            // type 2 query: path max query
            int u = rnd.next(1, N), v = rnd.next(1, N);
            if (u == v) v = u % N + 1;
            queries.push_back({2, u, v});
            cntType2++;
        }
    }
    // Ensure at least one type-2 query
    if (cntType2 == 0) {
        int u = rnd.next(1, N), v = rnd.next(1, N);
        if (u == v) v = u % N + 1;
        queries.back() = {2, u, v};
    }

    // 6. Output
    println(N);
    for (auto &e : edges) {
        println(e[0], e[1], e[2]);
    }
    println(M);
    for (auto &q : queries) {
        if (q[0] == 1) {
            // update
            println(1, q[1], q[2]);
        } else {
            // query
            println(2, q[1], q[2]);
        }
    }
    return 0;
}
