#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n: number of days
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    // Read daily wages T_i
    vector<int> t = inf.readInts(n, 1, 1000000, "T_i");
    inf.readEoln();

    // Additional global checks (optional, but we can verify problem's guarantee
    // that the answer exists and is finite by computing it).
    // Model: choose any contiguous interval [l, r] to work, payment is
    // (r - l + 1) * min(T_l..T_r). Maximize this value; also can choose not to work (0).
    // We ensure the computed maximum fits in 64-bit and is >= 0 (trivial given constraints).

    int N = n;
    vector<long long> A(N);
    for (int i = 0; i < N; ++i) A[i] = t[i];

    // Classic "largest rectangle in histogram" algorithm
    vector<int> st;
    long long best = 0;
    for (int i = 0; i <= N; ++i) {
        long long curH = (i < N ? A[i] : 0);
        while (!st.empty() && A[st.back()] >= curH) {
            long long h = A[st.back()];
            st.pop_back();
            int l = st.empty() ? 0 : (st.back() + 1);
            int r = i - 1;
            long long width = r - l + 1;
            long long val = h * width;
            if (val > best) best = val;
        }
        st.push_back(i);
    }

    // Ensure within expected bounds (theoretical max: n * max(T_i))
    long long maxTi = *max_element(A.begin(), A.end());
    long long theoreticalMax = maxTi * 1LL * N;
    ensuref(best >= 0, "Maximum profit is negative, which should be impossible.");
    ensuref(best <= theoreticalMax,
            "Maximum profit %lld exceeds theoretical upper bound %lld.",
            best, theoreticalMax);

    inf.readEof();
}
