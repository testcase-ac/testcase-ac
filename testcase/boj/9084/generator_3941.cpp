#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for number of test cases T
    double pt = rnd.next();
    int T;
    if (pt < 0.3) T = rnd.next(1, 3);
    else if (pt < 0.6) T = rnd.next(4, 7);
    else T = rnd.next(8, 10);

    println(T);
    for (int tc = 0; tc < T; tc++) {
        // Choose target M with small/medium/large bias, capped at 100
        double pm = rnd.next();
        int M;
        if (pm < 0.3) M = rnd.next(1, 10);
        else if (pm < 0.7) M = rnd.next(11, 50);
        else M = rnd.next(51, 100);

        // Determine coin value range, sometimes up to M, sometimes up to M*10 (≤10000)
        int coin_range_max;
        if (rnd.next() < 0.5) {
            coin_range_max = M;
        } else {
            int upper = min(10000, M * 10);
            if (upper <= M) upper = M;
            coin_range_max = rnd.next(M + 1, upper);
        }

        // Number of distinct coins N
        int maxN = min(20, coin_range_max);
        int N = rnd.next(1, maxN);

        // Generate N distinct coin values in [1, coin_range_max]
        set<int> coins;
        while ((int)coins.size() < N) {
            coins.insert(rnd.next(1, coin_range_max));
        }

        // Ensure at least one coin ≤ M to have some reachable ways
        bool hasSmall = false;
        for (int v : coins) {
            if (v <= M) { hasSmall = true; break; }
        }
        if (!hasSmall) {
            vector<int> tmp(coins.begin(), coins.end());
            int hi = (int)tmp.size() - 1;
            int idx = rnd.next(0, hi);
            coins.erase(tmp[idx]);
            coins.insert(rnd.next(1, M));
        }

        // Output this test case
        vector<int> vc(coins.begin(), coins.end());
        sort(vc.begin(), vc.end());
        println(N);
        println(vc);
        println(M);
    }

    return 0;
}
