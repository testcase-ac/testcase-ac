#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Possible small-to-medium N values for hand-checkable sizes
    vector<int> possibleNs = {5, 6, 7, 8, 9, 10, 15, 20};
    int T = rnd.next(1, 5);
    println(T);

    for (int tc = 0; tc < T; tc++) {
        int N = rnd.any(possibleNs);
        println(N);

        vector<int> L;
        int mode = rnd.next(0, 3);
        if (mode == 0) {
            // Distinct random heights
            int up = rnd.next(N, N * 5);
            vector<int> pool;
            for (int i = 1; i <= up; i++) pool.push_back(i);
            shuffle(pool.begin(), pool.end());
            L.assign(pool.begin(), pool.begin() + N);
        } else if (mode == 1) {
            // Few clusters of similar heights with small noise
            int clusters = rnd.next(1, 3);
            vector<int> bases;
            for (int i = 0; i < clusters; i++)
                bases.push_back(rnd.next(1, 1000));
            for (int i = 0; i < N; i++) {
                int b = rnd.any(bases);
                int noise = rnd.next(-2, 2);
                int h = max(1, b + noise);
                L.push_back(h);
            }
        } else if (mode == 2) {
            // Monotonically increasing pattern
            int start = rnd.next(1, 1000);
            L.push_back(start);
            for (int i = 1; i < N; i++) {
                int d = rnd.next(0, 5);
                L.push_back(L.back() + d);
            }
        } else {
            // All equal heights
            int h = rnd.next(1, 1000);
            L.assign(N, h);
        }

        // Shuffle input order to vary the arrangement
        shuffle(L.begin(), L.end());
        println(L);
    }
    return 0;
}
