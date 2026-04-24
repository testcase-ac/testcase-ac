#include "testlib.h"
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 6);
    for (int tc = 0; tc < T; tc++) {
        // number of vertices
        int N = rnd.next(1, 10);
        // number of components
        int K = rnd.next(1, N);
        // partition sizes
        vector<int> sizes(K, 1);
        int rem = N - K;
        for (int i = 0; i < rem; i++) {
            sizes[rnd.next(0, K - 1)]++;
        }
        // assign nodes to components
        vector<vector<int>> comps(K);
        int id = 1;
        for (int i = 0; i < K; i++) {
            for (int j = 0; j < sizes[i]; j++) {
                comps[i].push_back(id++);
            }
        }
        // choose which components will contain a cycle
        int cycCount = rnd.next(0, K);
        vector<int> idx(K);
        iota(idx.begin(), idx.end(), 0);
        shuffle(idx.begin(), idx.end());
        vector<bool> isCyclic(K, false);
        for (int i = 0; i < cycCount; i++) {
            isCyclic[idx[i]] = true;
        }
        // build edges
        vector<pair<int,int>> edges;
        for (int c = 0; c < K; c++) {
            auto nodes = comps[c];
            shuffle(nodes.begin(), nodes.end());
            int sz = nodes.size();
            // spanning tree
            vector<pair<int,int>> treeEdges;
            for (int i = 1; i < sz; i++) {
                int u = nodes[i];
                int v = nodes[rnd.next(0, i-1)];
                treeEdges.emplace_back(u, v);
            }
            for (auto &e : treeEdges) edges.push_back(e);
            // add extra edges if cyclic
            if (isCyclic[c] && sz > 1) {
                vector<pair<int,int>> possible;
                for (int i = 0; i < sz; i++) {
                    for (int j = i + 1; j < sz; j++) {
                        int u = nodes[i], v = nodes[j];
                        bool inTree = false;
                        for (auto &te : treeEdges) {
                            if ((te.first==u && te.second==v) || (te.first==v && te.second==u)) {
                                inTree = true; break;
                            }
                        }
                        if (!inTree) possible.emplace_back(u, v);
                    }
                }
                if (!possible.empty()) {
                    shuffle(possible.begin(), possible.end());
                    int extra = rnd.next(1, min((int)possible.size(), 2));
                    for (int i = 0; i < extra; i++) {
                        edges.push_back(possible[i]);
                    }
                }
            }
        }
        shuffle(edges.begin(), edges.end());
        // output case
        println(N, (int)edges.size());
        for (auto &e : edges) {
            println(e.first, e.second);
        }
    }
    println(0, 0);
    return 0;
}
