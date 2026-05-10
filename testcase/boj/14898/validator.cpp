#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXN = 1000000;
    const int MAXQ = 1000000;

    int N = inf.readInt(1, MAXN, "N");
    inf.readEoln();

    vector<int> A = inf.readInts(N, 1, 1000000000, "A_i");
    inf.readEoln();

    int Q = inf.readInt(1, MAXQ, "Q");
    inf.readEoln();

    vector<int> xs(Q), rs(Q);
    for (int i = 0; i < Q; ++i) {
        xs[i] = inf.readInt(-(N - 1), (N - 1), "x_i");
        inf.readSpace();
        rs[i] = inf.readInt(1, N, "r_i");
        inf.readEoln();
    }

    // simulate to check constraints involving l_i and that answers always exist / are valid
    vector<int> arr(N + 1);
    for (int i = 1; i <= N; ++i) arr[i] = A[i - 1];

    // For distinct count queries, we can answer by brute force with frequency map
    // Complexity: O(Q * N) worst-case; too big, but we only need to ensure constraints:
    // - 1 ≤ l_i ≤ r_i ≤ N. Those do not depend on frequency, only on x_i and previous answers.
    // The statement guarantees answers exist; there is no extra global property on answers
    // themselves (like bounded by X besides obvious r_i-l_i+1). So we only need to check l_i range.

    long long Qi_prev = 0; // Q_0 = 0
    for (int i = 0; i < Q; ++i) {
        long long li = xs[i] + Qi_prev;
        int ri = rs[i];

        ensuref(1 <= li && li <= ri && ri <= N,
                "Query %d has invalid interval: l_i = %lld, r_i = %d, N = %d",
                i + 1, li, ri, N);

        // We do not need to compute the actual answer for validation purposes,
        // just ensure it stays within provable bounds to detect overflow errors in generators.
        // Distinct count in [l, r] is between 1 and (r-l+1).
        long long len = ri - li + 1;
        ensuref(len >= 1 && len <= N,
                "Query %d length out of range: len = %lld", i + 1, len);

        // Compute the answer safely but efficiently enough:
        // Use unordered_set on subarray; although worst-case is large, validators are run
        // only during testing and typical data sizes should be manageable.
        unordered_set<int> st;
        st.reserve((size_t)len * 2);
        for (int pos = (int)li; pos <= ri; ++pos)
            st.insert(arr[pos]);
        long long Qi = (long long)st.size();

        ensuref(1 <= Qi && Qi <= len,
                "Query %d answer out of logical bounds: Q_i = %lld, len = %lld",
                i + 1, Qi, len);

        Qi_prev = Qi;
    }

    inf.readEof();
}
