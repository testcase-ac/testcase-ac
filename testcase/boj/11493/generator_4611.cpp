#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 5);
    println(T);

    for (int tc = 0; tc < T; tc++) {
        // Small graph size
        int N = rnd.next(2, 10);
        int maxE = N * (N - 1) / 2;

        // Hyper-parameter for density: tree, complete, or random
        double p = rnd.next();
        int M;
        if (p < 0.2) {
            M = N - 1;
        } else if (p < 0.4) {
            M = maxE;
        } else {
            M = rnd.next(N - 1, maxE);
        }

        // Build a random spanning tree
        vector<pair<int,int>> edges;
        vector<vector<bool>> used(N+1, vector<bool>(N+1, false));
        for (int i = 2; i <= N; i++) {
            int j = rnd.next(1, i - 1);
            edges.emplace_back(j, i);
            used[j][i] = used[i][j] = true;
        }

        // Prepare remaining possible edges
        vector<pair<int,int>> rem;
        for (int i = 1; i <= N; i++) {
            for (int j = i + 1; j <= N; j++) {
                if (!used[i][j]) rem.emplace_back(i, j);
            }
        }
        shuffle(rem.begin(), rem.end());

        // Add extra edges to reach M
        int extra = M - (N - 1);
        for (int i = 0; i < extra; i++) {
            edges.push_back(rem[i]);
        }

        // Shuffle final edge list
        shuffle(edges.begin(), edges.end());

        // Output graph
        println(N, M);
        for (auto &e : edges) {
            println(e.first, e.second);
        }

        // Node colors (0=black, 1=white)
        vector<int> node(N);
        for (int i = 0; i < N; i++) {
            node[i] = rnd.next(0, 1);
        }
        // Coin colors: same multiset as node colors, but randomized
        vector<int> coin = node;
        if (rnd.next(0, 1)) {
            shuffle(coin.begin(), coin.end());
        }

        // Output colors
        println(node);
        println(coin);
    }

    return 0;
}
