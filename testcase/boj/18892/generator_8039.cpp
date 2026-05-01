#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small to medium N for manual verification
    int N = rnd.next(2, 12);
    vector<int> A(N);
    int t = rnd.next(0, 3);
    if (t == 0) {
        // Random permutation
        for (int i = 0; i < N; i++) A[i] = i + 1;
        shuffle(A.begin(), A.end());
    } else if (t == 1) {
        // Increasing sequence
        for (int i = 0; i < N; i++) A[i] = i + 1;
    } else if (t == 2) {
        // Decreasing sequence
        for (int i = 0; i < N; i++) A[i] = N - i;
    } else {
        // Block shuffle: break into blocks of size 2 or 3
        vector<vector<int>> blocks;
        int cur = 1;
        while (cur <= N) {
            int rem = N - cur + 1;
            int bs = rnd.next(2, 3);
            if (bs > rem) bs = rem;
            vector<int> blk;
            for (int x = 0; x < bs; x++) blk.push_back(cur + x);
            blocks.push_back(blk);
            cur += bs;
        }
        shuffle(blocks.begin(), blocks.end());
        int idx = 0;
        for (auto &blk : blocks) {
            for (int v : blk) {
                A[idx++] = v;
            }
        }
    }
    // Compute LIS length and counts
    vector<int> dp(N, 1);
    vector<long long> cnt(N, 1);
    int L = 1;
    for (int i = 0; i < N; i++) {
        dp[i] = 1; cnt[i] = 1;
        for (int j = 0; j < i; j++) {
            if (A[j] < A[i]) {
                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    cnt[i] = cnt[j];
                } else if (dp[j] + 1 == dp[i]) {
                    cnt[i] += cnt[j];
                }
            }
        }
        L = max(L, dp[i]);
    }
    long long total = 0;
    for (int i = 0; i < N; i++) if (dp[i] == L) total += cnt[i];
    // Choose K: mostly valid, sometimes invalid to force -1
    long long K;
    if (rnd.next(0, 99) < 70) {
        // valid K
        K = rnd.next(1LL, total);
    } else {
        // invalid K
        K = total + rnd.next(1LL, 5LL);
    }
    // Output
    println(N, K);
    println(A);
    return 0;
}
