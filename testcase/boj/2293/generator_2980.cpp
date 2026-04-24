#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Sum to make
    int k = rnd.next(1, 20);
    // Number of coin types
    int maxN = min(8, k);
    int n = rnd.next(1, maxN);

    // Hyper-parameter: sometimes force a coin of value 1
    bool includeOne = rnd.next(0, 1);

    // Build a pool of possible coin values from 1..k
    vector<int> pool;
    for (int i = 1; i <= k; ++i) pool.push_back(i);
    shuffle(pool.begin(), pool.end());

    // Pick first n distinct values
    vector<int> coins(pool.begin(), pool.begin() + n);

    // Ensure coin "1" is included if requested
    if (includeOne) {
        bool has1 = false;
        for (int v : coins) if (v == 1) { has1 = true; break; }
        if (!has1) {
            int idx = rnd.next(0, n - 1);
            coins[idx] = 1;
        }
    }

    // Randomize order of coin types
    shuffle(coins.begin(), coins.end());

    // Output in required format
    println(n, k);
    for (int v : coins) println(v);

    return 0;
}
