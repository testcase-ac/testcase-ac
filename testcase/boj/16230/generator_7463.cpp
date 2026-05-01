#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
#include <numeric>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = rnd.next(2, 10);
    vector<pair<int,int>> edges;
    set<pair<int,int>> used;
    auto add_edge = [&](int u, int v) {
        int a = min(u, v), b = max(u, v);
        if (a == b) return;
        if (used.insert({a, b}).second) {
            edges.emplace_back(a, b);
        }
    };
    // prepare shuffled nodes for spanning structures
    vector<int> nodes(N);
    iota(nodes.begin(), nodes.end(), 1);
    shuffle(nodes.begin(), nodes.end());
    int t = rnd.next(0, 5);
    switch (t) {
        case 0: {
            // empty graph
            break;
        }
        case 1: {
            // complete graph
            for (int i = 1; i <= N; i++)
                for (int j = i + 1; j <= N; j++)
                    add_edge(i, j);
            break;
        }
        case 2: {
            // random tree
            for (int i = 1; i < N; i++) {
                int u = nodes[i];
                int v = nodes[rnd.next(0, i - 1)];
                add_edge(u, v);
            }
            break;
        }
        case 3: {
            // random cycle
            for (int i = 0; i < N; i++) {
                int u = nodes[i];
                int v = nodes[(i + 1) % N];
                add_edge(u, v);
            }
            break;
        }
        case 4: {
            // Erdős–Rényi random graph
            double p = rnd.next(0.0, 1.0);
            for (int i = 1; i <= N; i++)
                for (int j = i + 1; j <= N; j++)
                    if (rnd.next() < p)
                        add_edge(i, j);
            break;
        }
        case 5: {
            // exactly two components, each at least a tree plus extra edges
            int k = rnd.next(1, N - 1);
            vector<int> comp1(nodes.begin(), nodes.begin() + k);
            vector<int> comp2(nodes.begin() + k, nodes.end());
            shuffle(comp1.begin(), comp1.end());
            shuffle(comp2.begin(), comp2.end());
            // spanning trees
            for (int i = 1; i < (int)comp1.size(); i++)
                add_edge(comp1[i], comp1[rnd.next(0, i - 1)]);
            for (int i = 1; i < (int)comp2.size(); i++)
                add_edge(comp2[i], comp2[rnd.next(0, i - 1)]);
            // extra edges within each component
            double p2 = rnd.next(0.0, 1.0);
            auto add_extra = [&](const vector<int>& comp) {
                for (int i = 0; i < (int)comp.size(); i++)
                    for (int j = i + 1; j < (int)comp.size(); j++)
                        if (rnd.next() < p2)
                            add_edge(comp[i], comp[j]);
            };
            add_extra(comp1);
            add_extra(comp2);
            break;
        }
    }
    shuffle(edges.begin(), edges.end());
    int M = edges.size();
    println(N, M);
    for (auto &e : edges)
        println(e.first, e.second);
    return 0;
}
