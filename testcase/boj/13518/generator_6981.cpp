#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of nodes: small enough to verify by hand, up to 12
    int N = rnd.next(2, 12);

    // Hyper-parameter for tree shape: chain, star, or random
    int treeType = rnd.next(0, 2);
    vector<pair<int,int>> edges;
    if (treeType == 0) {
        // chain 1-2-3-...-N
        for (int i = 2; i <= N; i++)
            edges.emplace_back(i - 1, i);
    } else if (treeType == 1) {
        // star around a random center
        int center = rnd.next(1, N);
        for (int i = 1; i <= N; i++)
            if (i != center)
                edges.emplace_back(center, i);
    } else {
        // random tree by hooking each new node to a previous one
        for (int i = 2; i <= N; i++) {
            int p = rnd.next(1, i - 1);
            edges.emplace_back(p, i);
        }
    }
    // Randomize edge directions and order
    for (auto &e : edges)
        if (rnd.next(0, 1))
            swap(e.first, e.second);
    shuffle(edges.begin(), edges.end());

    // Vertex weights hyper-parameters: all equal, all distinct, or few distinct
    vector<int> weights(N);
    int wtType = rnd.next(0, 2);
    if (wtType == 0) {
        // all equal
        int w = rnd.next(1, 20);
        for (int i = 0; i < N; i++)
            weights[i] = w;
    } else if (wtType == 1) {
        // all distinct
        vector<int> pool;
        for (int v = 1; v <= 20; v++)
            pool.push_back(v);
        shuffle(pool.begin(), pool.end());
        for (int i = 0; i < N; i++)
            weights[i] = pool[i];
    } else {
        // limited distinct values (at most 5)
        int distinctCnt = rnd.next(1, min(N, 5));
        set<int> ss;
        while ((int)ss.size() < distinctCnt)
            ss.insert(rnd.next(1, 20));
        vector<int> pool(ss.begin(), ss.end());
        for (int i = 0; i < N; i++)
            weights[i] = rnd.any(pool);
    }

    // Number of queries: up to 20 for hand-checkability
    int M = rnd.next(1, min(20, N * N));
    vector<pair<int,int>> queries;
    for (int i = 0; i < M; i++) {
        int u, v;
        if (i < M / 4) {
            // trivial query u == v
            u = rnd.next(1, N);
            v = u;
        } else if (i < M / 2) {
            // query along a single edge
            auto e = rnd.any(edges);
            u = e.first;
            v = e.second;
        } else {
            // arbitrary pair
            u = rnd.next(1, N);
            v = rnd.next(1, N);
        }
        queries.emplace_back(u, v);
    }

    // Output in the required format
    println(N);
    println(weights);
    for (auto &e : edges)
        println(e.first, e.second);
    println(M);
    for (auto &q : queries)
        println(q.first, q.second);

    return 0;
}
