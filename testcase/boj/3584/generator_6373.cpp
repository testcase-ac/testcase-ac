#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // Choose number of nodes
        int N = rnd.next(2, 10);

        // Choose tree shape
        int shape = rnd.next(0, 3);
        vector<pair<int,int>> edges;
        if (shape == 0) {
            // Chain
            for (int i = 2; i <= N; i++)
                edges.emplace_back(i - 1, i);
        } else if (shape == 1) {
            // Star
            for (int i = 2; i <= N; i++)
                edges.emplace_back(1, i);
        } else if (shape == 2) {
            // Uniform random tree
            for (int i = 2; i <= N; i++) {
                int p = rnd.next(1, i - 1);
                edges.emplace_back(p, i);
            }
        } else {
            // Weighted bias
            for (int i = 2; i <= N; i++) {
                int t = rnd.next(-2, 2);
                int hi = i - 1;
                int k = rnd.wnext(hi, t) + 1; // parent in [1..i-1]
                edges.emplace_back(k, i);
            }
        }

        // Permute labels for variety
        vector<int> perm(N + 1);
        for (int i = 1; i <= N; i++) perm[i] = i;
        shuffle(perm.begin() + 1, perm.end());
        vector<pair<int,int>> outE;
        for (auto &e : edges) {
            outE.emplace_back(perm[e.first], perm[e.second]);
        }
        shuffle(outE.begin(), outE.end());

        // Pick query nodes (allow same occasionally)
        int u0, v0;
        if (rnd.next() < 0.2) {
            u0 = v0 = rnd.next(1, N);
        } else {
            u0 = rnd.next(1, N);
            do { v0 = rnd.next(1, N); } while (v0 == u0);
        }
        int u = perm[u0], v = perm[v0];

        // Output this test
        println(N);
        for (auto &e : outE) {
            println(e.first, e.second);
        }
        println(u, v);
    }

    return 0;
}
