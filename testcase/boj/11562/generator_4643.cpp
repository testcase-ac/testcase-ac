#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    vector<int> wts = {-1, 0, 1};
    int t1 = rnd.any(wts);
    int t2 = rnd.any(wts);
    int t3 = rnd.any(wts);
    int t4 = rnd.any(wts);

    // Number of nodes
    int N = rnd.next(2, 10);

    // Build a random spanning tree (undirected edges for connectivity)
    vector<int> nodes(N);
    for (int i = 0; i < N; i++) nodes[i] = i + 1;
    shuffle(nodes.begin(), nodes.end());
    set<pair<int,int>> treeSet;
    vector<pair<int,int>> edges;
    for (int i = 1; i < N; i++) {
        int u = nodes[i-1], v = nodes[i];
        if (u > v) swap(u, v);
        treeSet.insert({u, v});
        edges.emplace_back(u, v);
    }

    // Prepare candidate extra edges (undirected pairs not in tree)
    vector<pair<int,int>> cands;
    int max_extra = N*(N-1)/2 - (N-1);
    for (int i = 1; i <= N; i++) {
        for (int j = i+1; j <= N; j++) {
            if (!treeSet.count({i, j})) {
                cands.emplace_back(i, j);
            }
        }
    }
    // Choose how many extra edges to add
    int extra = 0;
    if (max_extra > 0) {
        extra = rnd.wnext(max_extra+1, t1);
    }
    shuffle(cands.begin(), cands.end());
    for (int i = 0; i < extra; i++) {
        edges.push_back(cands[i]);
    }
    int M = (int)edges.size();

    // Assign each edge a one-way (b=0) or two-way (b=1)
    double p_undir = rnd.next(); // probability of undirected
    vector<tuple<int,int,int>> finalEdges;
    finalEdges.reserve(M);
    for (auto &e : edges) {
        int u = e.first, v = e.second;
        int b = (rnd.next() < p_undir ? 1 : 0);
        finalEdges.emplace_back(u, v, b);
    }

    // Permute node labels for more diversity
    vector<int> perm(N);
    for (int i = 0; i < N; i++) perm[i] = i + 1;
    shuffle(perm.begin(), perm.end());
    for (auto &t : finalEdges) {
        int &u = get<0>(t), &v = get<1>(t);
        u = perm[u-1];
        v = perm[v-1];
    }

    // Questions
    int k = rnd.next(1, 20);
    vector<pair<int,int>> queries;
    queries.reserve(k);
    for (int i = 0; i < k; i++) {
        int s = rnd.wnext(N, t3) + 1;
        int e = rnd.wnext(N, t4) + 1;
        // apply same permutation
        s = perm[s-1];
        e = perm[e-1];
        queries.emplace_back(s, e);
    }

    // Output
    println(N, M);
    for (auto &t : finalEdges) {
        println(get<0>(t), get<1>(t), get<2>(t));
    }
    println(k);
    for (auto &q : queries) {
        println(q.first, q.second);
    }

    return 0;
}
