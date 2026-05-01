#include "testlib.h"
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of item types and capacity
    int N = rnd.next(3, 10);
    int M = rnd.next(10, 50);
    int T = max(1, M / 5); // threshold for light vs heavy items

    vector<tuple<int,int,int>> items;
    for (int i = 0; i < N; i++) {
        // Weight V: either light [1, T] or heavy [T+1, M]
        int V;
        if (rnd.next() < 0.5) {
            V = rnd.next(1, T);
        } else if (T + 1 <= M) {
            V = rnd.next(T + 1, M);
        } else {
            V = rnd.next(1, M);
        }

        // Value C: either high ratio [5V,10V] or low ratio [1,V]
        int C;
        if (rnd.next() < 0.5) {
            C = rnd.next(V * 5, V * 10);
        } else {
            C = rnd.next(1, V);
        }

        // Count K: if light, possibly large; if heavy, small
        int K;
        if (V <= T) {
            int maxK = 10000 / V;
            maxK = min(maxK, M * 2);
            maxK = max(maxK, 1);
            // Ensure at least M copies to allow unbounded-like behavior
            K = rnd.next(M, maxK);
        } else {
            K = rnd.next(1, 3);
        }

        items.emplace_back(V, C, K);
    }

    // Shuffle to avoid sorted patterns
    shuffle(items.begin(), items.end());

    // Output
    println(N, M);
    for (auto &t : items) {
        int V, C, K;
        tie(V, C, K) = t;
        println(V, C, K);
    }

    return 0;
}
