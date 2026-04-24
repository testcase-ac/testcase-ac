#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of cities
    int N = rnd.next(2, 10);

    // Generate a random topological order
    vector<int> ord(N);
    iota(ord.begin(), ord.end(), 1);
    shuffle(ord.begin(), ord.end());

    int s = ord.front();
    int t = ord.back();

    // Build a Hamiltonian path to ensure connectivity from s to t
    vector<pair<int,int>> edges;
    for (int i = 0; i + 1 < N; ++i) {
        edges.emplace_back(ord[i], ord[i+1]);
    }

    // Collect candidate extra edges (forward edges in topo order)
    vector<pair<int,int>> cand;
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            if (j == i + 1) continue;
            cand.emplace_back(ord[i], ord[j]);
        }
    }
    shuffle(cand.begin(), cand.end());

    // Hyper-parameter: how many extra edges to add, up to 10
    int extraCap = min((int)cand.size(), 10);
    int extra = rnd.next(0, extraCap);
    for (int i = 0; i < extra; ++i) {
        edges.push_back(cand[i]);
    }

    // Hyper-parameter: maximum edge weight
    int Wmax = rnd.next(1, 20);
    vector<tuple<int,int,int>> eds;
    for (auto &e : edges) {
        int w = rnd.next(1, Wmax);
        eds.emplace_back(e.first, e.second, w);
    }

    // Shuffle output order of edges
    shuffle(eds.begin(), eds.end());

    // Output format
    // First line: number of cities
    // Second line: number of roads
    println(N);
    println((int)eds.size());
    for (auto &tp : eds) {
        int u, v, w;
        tie(u, v, w) = tp;
        println(u, v, w);
    }
    // Last line: start and end cities
    println(s, t);

    return 0;
}
