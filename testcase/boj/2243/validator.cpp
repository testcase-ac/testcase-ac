#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// Fenwick tree for prefix sums and k-th order statistic
struct Fenwick {
    int n;
    vector<long long> f;
    Fenwick(int _n) : n(_n), f(n+1, 0) {}
    // add v at index i (1-based)
    void add(int i, long long v) {
        for (; i <= n; i += i & -i)
            f[i] += v;
    }
    // sum of [1..i]
    long long sum(int i) const {
        long long s = 0;
        for (; i > 0; i -= i & -i)
            s += f[i];
        return s;
    }
    // find smallest p in [1..n] such that sum(p) >= k; assume 1 <= k <= sum(n)
    int kth(long long k) const {
        int pos = 0;
        // highest power of two <= n
        for (int pw = 1 << 20; pw > 0; pw >>= 1) {
            if (pos + pw <= n && f[pos + pw] < k) {
                pos += pw;
                k -= f[pos];
            }
        }
        return pos + 1;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of operations
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    const int MAX_TASTE = 1000000;
    // track counts per taste
    vector<long long> cnt(MAX_TASTE + 1, 0);
    Fenwick fenw(MAX_TASTE);
    long long total = 0;

    for (int i = 1; i <= n; i++) {
        // Read operation type
        int A = inf.readInt(1, 2, "A_i");
        inf.readSpace();
        if (A == 1) {
            // Query: remove B-th smallest candy
            // ensure not empty
            ensuref(total >= 1,
                    "Operation %d: query on empty candy box", i);
            // B in [1, total]
            int B = inf.readInt(1, (int)total, "B_i");
            inf.readEoln();
            // find taste and remove one
            int taste = fenw.kth(B);
            // ensure we have at least one
            ensuref(cnt[taste] >= 1,
                    "Internal error at op %d: no candy of taste %d to remove", i, taste);
            cnt[taste]--;
            fenw.add(taste, -1);
            total--;
        } else {
            // A == 2: update count of a taste
            int B = inf.readInt(1, MAX_TASTE, "B_i");
            inf.readSpace();
            // C can be positive (add) or negative (remove)
            int C = inf.readInt(-2000000000, 2000000000, "C_i");
            inf.readEoln();
            // compute new count for taste B
            __int128 new_cnt = (__int128)cnt[B] + C;
            ensuref(new_cnt >= 0,
                    "Operation %d: removing too many candies of taste %d (have %lld, want to remove %d)",
                    i, B, cnt[B], -C);
            ensuref(new_cnt <= 2000000000LL,
                    "Operation %d: candy count for taste %d exceeds limit (now %lld)",
                    i, B, (long long)new_cnt);
            cnt[B] = (long long)new_cnt;
            // update total
            __int128 new_total = (__int128)total + C;
            ensuref(new_total >= 0 && new_total <= 2000000000LL,
                    "Operation %d: total candy count out of bounds after update (now %lld)",
                    i, (long long)new_total);
            total = (long long)new_total;
            // update Fenwick
            fenw.add(B, C);
        }
    }

    inf.readEof();
    return 0;
}
