#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int t = rnd.next(1, 7);
    println(t);

    for (int tc = 0; tc < t; tc++) {
        // Number of shops
        int n = rnd.next(1, 10);

        // Choose a pattern for positions
        int pattern = rnd.next(0, 4);
        vector<int> xs;

        if (pattern == 0) {
            // Pure random positions, allow some duplicates
            double dupProb = 0.2;
            for (int i = 0; i < n; i++) {
                if (!xs.empty() && rnd.next() < dupProb) {
                    xs.push_back(rnd.any(xs));
                } else {
                    xs.push_back(rnd.next(0, 99));
                }
            }
        }
        else if (pattern == 1) {
            // Distinct sorted positions
            vector<int> pool(100);
            iota(pool.begin(), pool.end(), 0);
            shuffle(pool.begin(), pool.end());
            pool.resize(n);
            sort(pool.begin(), pool.end());
            xs = pool;
        }
        else if (pattern == 2) {
            // Distinct reverse-sorted positions
            vector<int> pool(100);
            iota(pool.begin(), pool.end(), 0);
            shuffle(pool.begin(), pool.end());
            pool.resize(n);
            sort(pool.begin(), pool.end(), greater<int>());
            xs = pool;
        }
        else if (pattern == 3) {
            // Two clusters
            int c1 = rnd.next(0, 99);
            int c2 = rnd.next(0, 99);
            int d = rnd.next(1, 10);
            double dupProb = 0.1;
            for (int i = 0; i < n; i++) {
                int center = (rnd.next() < 0.5 ? c1 : c2);
                int lo = max(0, center - d);
                int hi = min(99, center + d);
                int v = rnd.next(lo, hi);
                if (!xs.empty() && rnd.next() < dupProb) {
                    xs.push_back(rnd.any(xs));
                } else {
                    xs.push_back(v);
                }
            }
        }
        else { // pattern == 4
            // Linearly spaced positions if possible, else random
            if (n > 1) {
                int maxStep = 99 / (n - 1);
                if (maxStep >= 1) {
                    int step = rnd.next(1, maxStep);
                    int start = rnd.next(0, 99 - step * (n - 1));
                    for (int i = 0; i < n; i++) {
                        xs.push_back(start + i * step);
                    }
                } else {
                    for (int i = 0; i < n; i++)
                        xs.push_back(rnd.next(0, 99));
                }
            } else {
                xs.push_back(rnd.next(0, 99));
            }
        }

        // Shuffle the list so it's not in pattern order
        shuffle(xs.begin(), xs.end());

        // Output this test case
        println(n);
        println(xs);
    }

    return 0;
}
