#include "testlib.h"
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small N for hand-checkable cases
    int N = rnd.next(2, 10);

    // Hyper-parameter to choose tree shape
    // 0 = chain, 1 = star, 2 = binary-like, 3 = random
    int type = rnd.next(0, 3);

    vector<pair<int,int>> edges;
    edges.reserve(N - 1);
    if (type == 0) {
        // Chain: 1-2-3-...-N
        for (int i = 1; i < N; i++) {
            edges.emplace_back(i, i + 1);
        }
    } else if (type == 1) {
        // Star centered at 1
        for (int i = 2; i <= N; i++) {
            edges.emplace_back(1, i);
        }
    } else if (type == 2) {
        // Binary-like: parent of i is floor(i/2)
        for (int i = 2; i <= N; i++) {
            edges.emplace_back(i / 2, i);
        }
    } else {
        // Uniform random tree: each new node connects to a random previous node
        for (int i = 2; i <= N; i++) {
            int p = rnd.next(1, i - 1);
            edges.emplace_back(p, i);
        }
    }

    // Hyper-parameter: optionally shuffle labels to disguise structure
    bool shuffleLabels = rnd.next(0, 1) == 1;
    if (shuffleLabels) {
        vector<int> perm(N + 1);
        iota(perm.begin(), perm.end(), 0);
        shuffle(perm.begin() + 1, perm.end());
        for (auto &e : edges) {
            e.first = perm[e.first];
            e.second = perm[e.second];
        }
    }

    // Hyper-parameter: randomly flip edge directions (still undirected)
    double flipProb = rnd.next(0.0, 1.0);
    for (auto &e : edges) {
        if (rnd.next() < flipProb) {
            swap(e.first, e.second);
        }
    }

    // Final shuffle of edge order
    shuffle(edges.begin(), edges.end());

    // Output
    println(N);
    for (auto &e : edges) {
        println(e.first, e.second);
    }
    return 0;
}
