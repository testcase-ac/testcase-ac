#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameter: choose small n divisible by 3 for hand-verifiable sizes
    vector<int> choices = {3, 6, 9, 12, 15};
    int n = rnd.any(choices);
    int K = 2 * n / 3;  // size of the guaranteed clique

    // Randomly pick which nodes form the 2n/3 clique
    vector<int> nodes(n);
    iota(nodes.begin(), nodes.end(), 1);
    shuffle(nodes.begin(), nodes.end());
    vector<char> inClique(n+1, false);
    for (int i = 0; i < K; i++) {
        inClique[nodes[i]] = true;
    }

    // Hyperparameter: probability of extra edges, biased by wnext for variety
    int t = rnd.any(vector<int>{-1, 0, 1});
    double p = rnd.wnext(100, t) / 100.0;

    // Build edges: all pairs in the clique, plus extra edges with probability p
    vector<pair<int,int>> edges;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (inClique[i] && inClique[j]) {
                edges.emplace_back(i, j);
            } else if (rnd.next() < p) {
                edges.emplace_back(i, j);
            }
        }
    }

    // Shuffle output order for added randomness
    shuffle(edges.begin(), edges.end());

    // Output
    println(n, edges.size());
    for (auto &e : edges) {
        println(e.first, e.second);
    }

    return 0;
}
