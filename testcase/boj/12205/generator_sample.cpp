#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const long long LIM = 1000000000000000000LL;

long long capAdd(long long a, long long b) {
    if (a > LIM - b) return LIM;
    return a + b;
}

vector<long long> catalanTable(int maxN) {
    vector<long long> catalan(maxN + 1);
    for (int target = 1; target <= maxN; ++target) {
        vector<vector<long long>> dp(target + 1, vector<long long>(target + 1, 0));
        dp[0][0] = 1;
        for (int len = 0; len < 2 * target; ++len) {
            vector<vector<long long>> next(target + 1, vector<long long>(target + 1, 0));
            for (int open = 0; open <= target; ++open) {
                for (int bal = 0; bal <= target; ++bal) {
                    long long cur = dp[open][bal];
                    if (cur == 0) continue;
                    if (open < target) next[open + 1][bal + 1] = capAdd(next[open + 1][bal + 1], cur);
                    if (bal > 0) next[open][bal - 1] = capAdd(next[open][bal - 1], cur);
                }
            }
            dp.swap(next);
        }
        catalan[target] = dp[target][0];
    }
    return catalan;
}

long long randomK(long long lo, long long hi) {
    if (lo == hi) return lo;
    return rnd.next(lo, hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<long long> catalan = catalanTable(35);
    int mode = rnd.next(0, 5);
    int t = rnd.next(1, mode == 3 ? 20 : 12);
    vector<pair<int, long long>> cases;

    for (int i = 0; i < t; ++i) {
        int n;
        long long k;

        if (mode == 0) {
            n = rnd.next(1, 9);
            long long total = catalan[n];
            vector<long long> choices = {1, 2, total, min(LIM, total + 1)};
            k = rnd.any(choices);
        } else if (mode == 1) {
            n = rnd.next(10, 35);
            long long total = catalan[n];
            if (rnd.next(0, 1) == 0) {
                k = randomK(1, min(total, 1000000LL));
            } else {
                long long lo = max(1LL, total - 1000000LL);
                k = randomK(lo, total);
            }
        } else if (mode == 2) {
            n = rnd.next(1, 20);
            long long total = catalan[n];
            long long delta = rnd.next(1LL, 1000000LL);
            k = min(LIM, total + delta);
        } else if (mode == 3) {
            n = rnd.next(1, 100);
            int bucket = rnd.next(0, 4);
            if (bucket == 0) k = rnd.next(1LL, 20LL);
            else if (bucket == 1) k = rnd.next(1LL, 1000000LL);
            else if (bucket == 2) k = rnd.next(999999999999000000LL, LIM);
            else if (n <= 35) k = randomK(1, catalan[n]);
            else k = rnd.next(1LL, LIM);
        } else {
            n = rnd.any(vector<int>{1, 2, 3, 34, 35, 36, 50, 100});
            if (n <= 35 && rnd.next(0, 2) != 0) {
                long long total = catalan[n];
                k = rnd.any(vector<long long>{1, total, min(LIM, total + 1)});
            } else {
                k = rnd.any(vector<long long>{1, 2, 999999999999999999LL, LIM});
            }
        }

        cases.push_back({n, k});
    }

    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (const auto& tc : cases) println(tc.first, tc.second);

    return 0;
}
