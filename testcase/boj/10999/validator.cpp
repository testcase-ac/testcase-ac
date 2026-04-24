#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
using namespace std;

// Helper to convert __int128 to string for error messages
static string i128_to_string(__int128 x) {
    if (x == 0) return "0";
    bool neg = false;
    if (x < 0) {
        neg = true;
        x = -x;
    }
    string s;
    while (x > 0) {
        int digit = int(x % 10);
        s.push_back(char('0' + digit));
        x /= 10;
    }
    if (neg) s.push_back('-');
    reverse(s.begin(), s.end());
    return s;
}

// Fenwick tree supporting range add and prefix sum
struct BIT {
    int n;
    vector<__int128> t;
    BIT(int _n = 0) : n(_n), t(n+1, 0) {}
    void add(int idx, __int128 v) {
        for (; idx <= n; idx += idx & -idx) {
            t[idx] += v;
        }
    }
    __int128 sum(int idx) const {
        __int128 s = 0;
        for (; idx > 0; idx -= idx & -idx) {
            s += t[idx];
        }
        return s;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Constants for full 64-bit signed range
    const long long MINLL = -9223372036854775807LL - 1;
    const long long MAXLL =  9223372036854775807LL;

    // Read N, M, K
    long long N_ll = inf.readLong(1LL, 1000000LL, "N");
    inf.readSpace();
    int M = inf.readInt(1, 10000, "M");
    inf.readSpace();
    int K = inf.readInt(1, 10000, "K");
    inf.readEoln();

    int N = int(N_ll);

    // Read initial array
    vector<long long> A(N+1);
    for (int i = 1; i <= N; i++) {
        A[i] = inf.readLong(MINLL, MAXLL, "A_i");
        inf.readEoln();
    }

    // Prepare Fenwick trees for range add & range sum
    // We need to support index up to N+1 for c+1 updates
    BIT bit1(N+1), bit2(N+1);
    // Build initial array into BIT by doing range_add(i, i, A[i])
    for (int i = 1; i <= N; i++) {
        long long v = A[i];
        // range_add(i, i, v)
        bit1.add(i, v);
        bit1.add(i+1, -(__int128)v);
        bit2.add(i, -(__int128)v * (i - 1));
        bit2.add(i+1, (__int128)v * i);
    }

    int cnt_update = 0, cnt_query = 0;
    int total_ops = M + K;
    for (int op = 1; op <= total_ops; op++) {
        int a = inf.readInt(1, 2, "a");
        inf.readSpace();
        int b = inf.readInt(1, N, "b");
        inf.readSpace();
        int c = inf.readInt(1, N, "c");
        ensuref(b <= c,
                "Operation %d: b (%d) must be <= c (%d)", op, b, c);
        if (a == 1) {
            // update: a b c d
            inf.readSpace();
            long long d = inf.readLong(MINLL, MAXLL, "d");
            inf.readEoln();
            cnt_update++;
            // apply range_add(b, c, d)
            bit1.add(b, d);
            bit1.add(c+1, -(__int128)d);
            bit2.add(b, -(__int128)d * (b - 1));
            bit2.add(c+1, (__int128)d * c);
        } else {
            // query: a b c
            inf.readEoln();
            cnt_query++;
            // compute prefix_sum(x) = bit1.sum(x)*x + bit2.sum(x)
            auto prefix = [&](int x) {
                __int128 s1 = bit1.sum(x);
                __int128 s2 = bit2.sum(x);
                return s1 * x + s2;
            };
            __int128 sum_r = prefix(c);
            __int128 sum_l1 = (b > 1 ? prefix(b-1) : 0);
            __int128 ans = sum_r - sum_l1;
            // validate answer within 64-bit signed range
            ensuref(ans >= MINLL && ans <= MAXLL,
                    "Query %d result %s is out of 64-bit range",
                    op, i128_to_string(ans).c_str());
        }
    }

    // Validate counts
    ensuref(cnt_update == M,
            "Number of updates %d does not match M (%d)",
            cnt_update, M);
    ensuref(cnt_query == K,
            "Number of queries %d does not match K (%d)",
            cnt_query, K);

    inf.readEof();
    return 0;
}
