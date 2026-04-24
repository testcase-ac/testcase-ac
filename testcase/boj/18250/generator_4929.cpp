#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small graph: 2 <= N <= 6
    int N = rnd.next(2, 6);
    // Number of components: at least 1, at most min(N-1,3)
    int maxComp = min(N - 1, 3);
    int K = rnd.next(1, maxComp);

    // Random partition of N into K positive sizes
    vector<int> compSizes;
    int rem = N;
    for (int i = 1; i < K; i++) {
        int sz = rnd.next(1, rem - (K - i));
        compSizes.push_back(sz);
        rem -= sz;
    }
    compSizes.push_back(rem);

    // Assign node labels randomly to components
    vector<int> nodes(N);
    for (int i = 0; i < N; i++) nodes[i] = i + 1;
    shuffle(nodes.begin(), nodes.end());
    int pos = 0;

    // Build edges
    vector<pair<int,int>> edges;
    for (int cs : compSizes) {
        vector<int> comp(nodes.begin() + pos, nodes.begin() + pos + cs);
        pos += cs;
        if (cs < 2) continue; // no edges for singleton

        // Choose component type: 0=tree, 1=cycle (if possible), 2=random
        int t = rnd.next(0, 2);
        if (t == 1 && cs < 3) t = 0; // for size 2, treat cycle as tree

        if (t == 0) {
            // Random tree
            for (int i = 1; i < cs; i++) {
                int j = rnd.next(0, i - 1);
                edges.emplace_back(comp[i], comp[j]);
            }
        } else if (t == 1) {
            // Simple cycle
            for (int i = 0; i < cs; i++) {
                int u = comp[i];
                int v = comp[(i + 1) % cs];
                edges.emplace_back(u, v);
            }
        } else {
            // Random general graph with at least one edge
            vector<pair<int,int>> all;
            for (int i = 0; i < cs; i++) {
                for (int j = i + 1; j < cs; j++) {
                    all.emplace_back(comp[i], comp[j]);
                }
            }
            shuffle(all.begin(), all.end());
            int Emax = (int)all.size();
            // cap per component to keep total small
            int cap = min(Emax, rnd.next(1, Emax));
            int E = rnd.next(1, cap);
            all.resize(E);
            for (auto &e : all) edges.push_back(e);
        }
    }

    // Ensure at least one edge
    if (edges.empty()) {
        // pick two distinct nodes
        int u = rnd.next(1, N), v = rnd.next(1, N);
        while (v == u) v = rnd.next(1, N);
        edges.emplace_back(u, v);
    }
    // Cap total edges to <=20
    if ((int)edges.size() > 20) {
        shuffle(edges.begin(), edges.end());
        edges.resize(rnd.next(1, 20));
    }

    // Output
    int M = edges.size();
    println(N, M);
    for (auto &e : edges) {
        println(e.first, e.second);
    }
    return 0;
}
