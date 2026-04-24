#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose N small enough for manual verification
    int N = rnd.next(1, 12);
    bool unsolvable = (N >= 3) && (rnd.next() < 0.3);

    vector<pair<int,int>> shirts;
    if (unsolvable) {
        // Force an impossible case: more shirts than distinct numbers
        N = rnd.next(3, 6);
        int x = rnd.next(1, 5);
        int y;
        do {
            y = rnd.next(1, 5);
        } while (y == x);
        for (int i = 0; i < N; i++) {
            int a = x, b = y;
            if (rnd.next() < 0.5) swap(a, b);
            shirts.emplace_back(a, b);
        }
    } else {
        // Construct a solvable case by ensuring a perfect matching
        int maxNum = rnd.next(N, N * 2 + 1);
        vector<int> pool;
        for (int i = 1; i <= maxNum; i++)
            pool.push_back(i);
        shuffle(pool.begin(), pool.end());
        vector<int> primary(pool.begin(), pool.begin() + N);

        for (int i = 0; i < N; i++) {
            int a = primary[i];
            int b;
            double p = rnd.next();
            if (p < 0.4) {
                // same number on both sides
                b = a;
            } else if (p < 0.7) {
                // pick another primary to create collisions
                b = rnd.any(primary);
            } else {
                // pick any number in range
                b = rnd.next(1, maxNum);
            }
            // sometimes swap to hide the perfect matching
            if (rnd.next() < 0.3) swap(a, b);
            shirts.emplace_back(a, b);
        }
    }

    // Output
    println(N);
    for (auto &pr : shirts) {
        println(pr.first, pr.second);
    }
    return 0;
}
