#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(3, 5);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // number of islands
        int N = rnd.next(2, 8);
        // build a spanning tree first to ensure connectivity
        vector<tuple<int,int,int,int>> edges;
        for (int i = 1; i < N; i++) {
            int u = i, v = i + 1;
            int t = rnd.next(1, 5);
            int g = rnd.next(1, 5);
            edges.emplace_back(u, v, t, g);
        }
        // hyper-parameters for extra edges
        double shortcutProb = rnd.next();
        double heavyProb = rnd.next();
        // maximum extra edges limited to at most 3 and graph completeness
        int maxPairs = N * (N - 1) / 2;
        int hiExtra = maxPairs - (N - 1);
        int extra = (hiExtra > 0 ? rnd.next(0, min(hiExtra, 3)) : 0);
        for (int i = 0; i < extra; i++) {
            int u = rnd.next(1, N);
            int v = rnd.next(1, N);
            if (u == v) v = u % N + 1;
            int t, g;
            // make some edges likely shortcuts
            if (rnd.next() < shortcutProb) {
                t = rnd.next(1, 2);
            } else {
                t = rnd.next(3, 6);
            }
            // some edges with high garnet rewards
            if (rnd.next() < heavyProb) {
                g = rnd.next(6, 10);
            } else {
                g = rnd.next(1, 5);
            }
            edges.emplace_back(u, v, t, g);
        }
        // shuffle edge order for diversity
        shuffle(edges.begin(), edges.end());
        int M = edges.size();
        // output this test case
        println(N, M);
        for (auto &e : edges) {
            int u, v, t, g;
            tie(u, v, t, g) = e;
            println(u, v, t, g);
        }
    }
    return 0;
}
