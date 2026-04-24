#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameters
    int n = rnd.next(2, 10);
    int k = rnd.next(1, 20);
    int maxCoord = rnd.next(5, 20);
    bool chain = rnd.next(0, 1) == 1;
    double overlapProb = rnd.next();

    vector<pair<int,int>> segs;
    if (chain) {
        // Chain-like intervals
        int firstL = rnd.next(0, maxCoord / 2);
        int firstR = firstL + rnd.next(1, maxCoord / 2 + 1);
        segs.emplace_back(firstL, firstR);
        int prevL = firstL, prevR = firstR;
        for (int i = 1; i < n; i++) {
            int L;
            if (rnd.next() < overlapProb) {
                // overlap with previous
                L = rnd.next(prevL + 1, prevR);
            } else {
                // gap after previous
                L = prevR + rnd.next(1, 3);
            }
            int R = L + rnd.next(1, maxCoord / 2 + 1);
            segs.emplace_back(L, R);
            prevL = L; prevR = R;
        }
    } else {
        // Random distinct left endpoints
        int poolMax = rnd.next(n, n + 20);
        vector<int> pool;
        for (int x = 0; x <= poolMax; x++) pool.push_back(x);
        shuffle(pool.begin(), pool.end());
        pool.resize(n);
        sort(pool.begin(), pool.end());
        for (int L : pool) {
            int R = L + rnd.next(1, maxCoord / 2 + 1);
            segs.emplace_back(L, R);
        }
    }

    // Visit sequence
    vector<int> visits(k);
    for (int i = 0; i < k; i++) {
        visits[i] = rnd.next(1, n);
    }

    // Output
    println(n, k);
    for (auto &p : segs) {
        println(p.first, p.second);
    }
    println(visits);

    return 0;
}
