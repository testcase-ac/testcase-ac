#include "testlib.h"
#include <vector>
#include <tuple>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose graph size
    int mode = rnd.next(0, 2);
    int N;
    if (mode == 0) {
        N = rnd.next(2, 5);
    } else if (mode == 1) {
        N = rnd.next(6, 12);
    } else {
        N = rnd.next(13, 20);
    }

    // All node IDs
    vector<int> nodes(N);
    iota(nodes.begin(), nodes.end(), 1);
    shuffle(nodes.begin(), nodes.end());

    // Decide reachable component size
    int compSize = rnd.next(1, N);
    vector<int> compNodes(nodes.begin(), nodes.begin() + compSize);
    vector<int> unreachable(nodes.begin() + compSize, nodes.end());

    // Start node must be in reachable component
    int K = rnd.any(compNodes);

    // Bias for weights: -1 small, 0 uniform, +1 large
    int weightBias = rnd.next(-1, 1);

    vector<tuple<int,int,int>> edges;

    // 1) Build a spanning tree rooted at K over compNodes
    if (compSize > 1) {
        vector<int> treeNodes = {K};
        vector<int> others;
        for (int v : compNodes) if (v != K) others.push_back(v);
        shuffle(others.begin(), others.end());
        for (int v : others) {
            int u = rnd.any(treeNodes);
            int w = rnd.wnext(10, weightBias) + 1;
            edges.emplace_back(u, v, w);
            treeNodes.push_back(v);
        }
    }

    // 2) Extra edges among reachable nodes
    int extraR = rnd.next(0, compSize * 2);
    for (int i = 0; i < extraR; i++) {
        int u = rnd.any(compNodes);
        int v = rnd.any(compNodes);
        if (v == u) {
            if (compSize > 1) {
                auto it = find(compNodes.begin(), compNodes.end(), u);
                int idx = (int)(it - compNodes.begin());
                v = compNodes[(idx + 1) % compSize];
            } else {
                continue;
            }
        }
        int w = rnd.wnext(10, weightBias) + 1;
        edges.emplace_back(u, v, w);
    }

    // 3) Edges from unreachable nodes (keeps them unreachable from K)
    if (!unreachable.empty()) {
        int extraU = rnd.next(0, (int)unreachable.size());
        for (int i = 0; i < extraU; i++) {
            int u = rnd.any(unreachable);
            int v = rnd.any(nodes);
            if (v == u) {
                do { v = rnd.any(nodes); } while (v == u);
            }
            int w = rnd.wnext(10, weightBias) + 1;
            edges.emplace_back(u, v, w);
        }
    }

    // Ensure at least one edge exists
    if (edges.empty()) {
        int u = K;
        int v = rnd.next(1, N);
        if (v == u) v = (u % N) + 1;
        int w = rnd.next(1, 10);
        edges.emplace_back(u, v, w);
    }

    // Shuffle edges for randomness
    shuffle(edges.begin(), edges.end());

    // Output
    int E = edges.size();
    println(N, E);
    println(K);
    for (auto &e : edges) {
        int u, v, w;
        tie(u, v, w) = e;
        println(u, v, w);
    }
    return 0;
}
