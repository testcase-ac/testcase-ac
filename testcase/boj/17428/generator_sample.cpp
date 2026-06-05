#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long maxKForN(int n) {
    return (1LL << n) - 1;
}

long long catalanCount(int pairs) {
    vector<vector<long long>> dp(pairs + 1, vector<long long>(pairs + 2, 0));
    dp[0][0] = 1;
    for (int pos = 0; pos < 2 * pairs; ++pos) {
        vector<vector<long long>> next(pairs + 1, vector<long long>(pairs + 2, 0));
        for (int open = 0; open <= pairs; ++open) {
            for (int balance = 0; balance <= pairs; ++balance) {
                long long cur = dp[open][balance];
                if (cur == 0) continue;
                if (open < pairs) next[open + 1][balance + 1] += cur;
                if (balance > 0) next[open][balance - 1] += cur;
            }
        }
        dp.swap(next);
    }
    return dp[pairs][0];
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    long long k;

    if (mode == 0) {
        n = rnd.next(1, 8) * 2;
        k = 0;
    } else if (mode == 1) {
        n = rnd.next(1, 8) * 2;
        k = maxKForN(n);
    } else if (mode == 2) {
        n = rnd.next(1, 10) * 2;
        long long c = catalanCount(n / 2);
        k = max(0LL, c - 1);
    } else if (mode == 3) {
        n = rnd.next(2, 10) * 2;
        long long c = catalanCount(n / 2);
        k = min(maxKForN(n), c + rnd.next(0, 5));
    } else if (mode == 4) {
        n = rnd.next(15, 25) * 2;
        k = rnd.next(0LL, maxKForN(n));
    } else if (mode == 5) {
        n = 50;
        k = rnd.next(0LL, maxKForN(n));
    } else if (mode == 6) {
        n = rnd.next(1, 25) * 2;
        int bit = rnd.next(0, n);
        k = min(maxKForN(n), (1LL << bit) - 1 + rnd.next(0, 3));
    } else {
        n = rnd.next(1, 25) * 2;
        long long hi = min(maxKForN(n), 2000LL);
        k = rnd.next(0LL, hi);
    }

    println(n, k);
    return 0;
}
