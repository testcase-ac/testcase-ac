#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAX_N = 100000;
    const int maxCheck = 1000;
    const int INF = (int)1e9;
    int coins[4] = {1, 2, 5, 7};

    // Precompute optimal (DP) and greedy counts for n up to maxCheck
    vector<int> dp(maxCheck + 1, INF);
    dp[0] = 0;
    for (int i = 1; i <= maxCheck; ++i) {
        for (int c : coins) {
            if (i >= c && dp[i - c] + 1 < dp[i]) {
                dp[i] = dp[i - c] + 1;
            }
        }
    }

    auto greedy = [&](int n) {
        int cnt = 0;
        int vals[4] = {7, 5, 2, 1};
        for (int c : vals) {
            int take = n / c;
            cnt += take;
            n -= take * c;
        }
        return cnt;
    };

    vector<int> greedyFail;
    for (int i = 1; i <= maxCheck; ++i) {
        int g = greedy(i);
        if (dp[i] < g) {
            greedyFail.push_back(i);
        }
    }

    int N = 0;

    while (true) {
        int type = rnd.next(0, 6); // 7 scenario types

        if (type == 0) {
            // Exact edge: zero amount
            N = 0;
        } else if (type == 1) {
            // Small amounts, easy to verify manually
            N = rnd.next(1, 20);
        } else if (type == 2) {
            // Small/medium amounts
            N = rnd.next(21, 200);
        } else if (type == 3) {
            // Near multiples / interesting bases
            int bases[] = {5, 7, 10, 14, 21, 28};
            int base = bases[rnd.next(0, 5)];
            int maxK = MAX_N / base;
            if (maxK < 1) maxK = 1;
            int k = rnd.next(1, maxK);
            int offset = rnd.next(-3, 3);
            N = base * k + offset;
        } else if (type == 4) {
            // Full range, skewed towards larger values sometimes
            int t = rnd.any(vector<int>{0, 3, 5});
            int x = (t == 0 ? rnd.next(0, MAX_N) : rnd.wnext(MAX_N + 1, t));
            N = x;
        } else if (type == 5) {
            // Values where greedy fails
            if (!greedyFail.empty()) {
                N = rnd.any(greedyFail);
            } else {
                N = 10; // known greedy-fail example
            }
        } else if (type == 6) {
            // Near maximum
            N = MAX_N - rnd.next(0, 20);
        }

        if (0 <= N && N <= MAX_N) break;
    }

    println(N);
    return 0;
}
