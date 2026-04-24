#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // Number of buildings
        int N = rnd.next(2, 15);
        // Generate a random topological order
        vector<int> order(N);
        iota(order.begin(), order.end(), 1);
        shuffle(order.begin(), order.end());
        // Build a spanning chain to ensure reachability
        vector<pair<int,int>> edges;
        for (int i = 0; i + 1 < N; i++) {
            edges.emplace_back(order[i], order[i+1]);
        }
        // Collect all other possible edges (i -> j for i<j in topo order)
        vector<pair<int,int>> extraPool;
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                if (j == i + 1) continue;
                extraPool.emplace_back(order[i], order[j]);
            }
        }
        // Shuffle and pick a weighted number of extra edges
        shuffle(extraPool.begin(), extraPool.end());
        int rem = (int)extraPool.size();
        int t = rnd.next(-2, 2);
        int extra = rnd.wnext(rem + 1, t);
        for (int i = 0; i < extra; i++) {
            edges.push_back(extraPool[i]);
        }
        int K = edges.size();
        // Build construction times
        vector<int> D(N);
        for (int i = 0; i < N; i++) {
            D[i] = rnd.wnext(100001, rnd.next(-2, 2));
        }
        // Target building
        int W = rnd.next(1, N);

        // Output this test case
        println(N, K);
        println(D);
        for (auto &e : edges) {
            println(e.first, e.second);
        }
        println(W);
    }
    return 0;
}
