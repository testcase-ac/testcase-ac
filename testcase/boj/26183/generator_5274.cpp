#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of suspects (small for hand‐checking)
    int n = rnd.next(1, 10);

    // Hyper‐parameters for arrival and duration ranges
    int maxA = rnd.next(n, 15);
    int maxT = rnd.next(n, 15);

    // Bias parameters for uneven distributions
    int biasA = rnd.next(-2, 2);
    int biasT = rnd.next(-2, 2);

    // Track used durations per arrival time
    vector<vector<bool>> used(maxA + 1, vector<bool>(maxT + 1, false));
    vector<pair<int,int>> v;
    v.reserve(n);

    for (int i = 0; i < n; i++) {
        // Sample arrival time in [1..maxA] with bias
        int a = rnd.wnext(maxA, biasA) + 1;

        // Sample a unique duration for this arrival
        int t;
        do {
            t = rnd.wnext(maxT, biasT) + 1;
        } while (used[a][t]);
        used[a][t] = true;

        v.emplace_back(a, t);
    }

    // Randomly decide to sort by (arrival, duration) or shuffle
    double sortProb = rnd.next();
    if (rnd.next() < sortProb) {
        sort(v.begin(), v.end(), [](auto &p, auto &q) {
            if (p.first != q.first) return p.first < q.first;
            return p.second < q.second;
        });
    } else {
        shuffle(v.begin(), v.end());
    }

    // Output in the required format
    println(n);
    for (auto &p : v)
        println(p.first, p.second);

    return 0;
}
