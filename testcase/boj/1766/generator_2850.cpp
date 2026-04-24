#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of problems at least 2 to ensure at least one dependency
    int N = rnd.next(2, 10);

    // Decide a base topological order
    vector<int> perm(N);
    iota(perm.begin(), perm.end(), 1);
    if (rnd.next() < 0.7) {
        shuffle(perm.begin(), perm.end());
    }

    // Build all possible DAG edges respecting perm-order
    vector<pair<int,int>> initCandidates;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            initCandidates.emplace_back(perm[i], perm[j]);
        }
    }
    vector<pair<int,int>> candidates = initCandidates;

    // With some probability, enforce a chain to connect the graph
    bool buildChain = (rnd.next() < 0.4);
    vector<pair<int,int>> chainEdges;
    if (buildChain) {
        for (int i = 0; i + 1 < N; i++) {
            chainEdges.emplace_back(perm[i], perm[i+1]);
        }
        // Remove chain edges from candidates to avoid duplicates
        vector<pair<int,int>> filtered;
        for (auto &e : candidates) {
            bool isChain = false;
            for (auto &c : chainEdges) {
                if (e == c) { isChain = true; break; }
            }
            if (!isChain) filtered.push_back(e);
        }
        candidates.swap(filtered);
    }

    // Decide how many extra edges to add (up to 20) with weighted randomness
    int capM = min((int)candidates.size(), 20);
    vector<int> ts = {-2, -1, 0, 1, 2};
    int t = rnd.any(ts);
    int M_rem = rnd.wnext(capM + 1, t);  // in [0..capM]
    
    // Collect edges
    shuffle(candidates.begin(), candidates.end());
    vector<pair<int,int>> edges = chainEdges;
    for (int i = 0; i < M_rem; i++) {
        edges.push_back(candidates[i]);
    }
    shuffle(edges.begin(), edges.end());

    // Ensure at least one dependency edge (M >= 1)
    if (edges.empty()) {
        shuffle(initCandidates.begin(), initCandidates.end());
        edges.push_back(initCandidates[0]);
    }

    // Output
    int M = edges.size();
    println(N, M);
    for (auto &e : edges) {
        println(e.first, e.second);
    }

    return 0;
}
