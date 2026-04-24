#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // number of people/books
    int N = rnd.next(2, 10);
    // decide whether to generate a YES-case (perfect matching exists) or NO-case
    bool make_yes = rnd.next(0, 1) == 1;

    vector<pair<int,int>> edges;

    if (make_yes) {
        // Build a derangement permutation p so that p[i] != i
        vector<int> p(N);
        iota(p.begin(), p.end(), 0);
        bool has_fixed;
        do {
            shuffle(p.begin(), p.end());
            has_fixed = false;
            for (int i = 0; i < N; i++) {
                if (p[i] == i) {
                    has_fixed = true;
                    break;
                }
            }
        } while (has_fixed);
        // Add cycle-cover edges
        for (int i = 0; i < N; i++) {
            edges.emplace_back(i, p[i]);
        }
        // Prepare extra candidate edges (no self-loops, no duplicates of the cycle edges)
        vector<pair<int,int>> cand;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (i != j && p[i] != j) {
                    cand.emplace_back(i, j);
                }
            }
        }
        shuffle(cand.begin(), cand.end());
        // Add a random number of extra edges
        int extra = cand.empty() ? 0 : rnd.next(0, (int)cand.size());
        for (int i = 0; i < extra; i++) {
            edges.push_back(cand[i]);
        }
    } else {
        // Build a NO-case by isolating one node's outgoing edges
        int u = rnd.next(0, N - 1);
        vector<pair<int,int>> cand;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (i != j && i != u) {
                    cand.emplace_back(i, j);
                }
            }
        }
        shuffle(cand.begin(), cand.end());
        // Must have at least one edge (M>=1)
        int M = cand.empty() ? 0 : rnd.next(1, (int)cand.size());
        for (int i = 0; i < M; i++) {
            edges.push_back(cand[i]);
        }
    }

    // Final shuffle of all edges for randomness
    shuffle(edges.begin(), edges.end());
    // Output
    println(N, (int)edges.size());
    for (auto &e : edges) {
        println(e.first, e.second);
    }
    return 0;
}
