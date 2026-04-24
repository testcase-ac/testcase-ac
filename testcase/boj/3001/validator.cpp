#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

long long A, B;
int S;
int L;
vector<int> ld, hd;
int8_t dp_memo[20][2][2][140]; // -1 unset, 0 false, 1 true

// dfs returns whether there exists a number between the padded bounds
bool dfs(int pos, bool tightLow, bool tightHigh, int sum) {
    if (sum > S) return false;
    if (pos == L) {
        return sum == S;
    }
    int8_t &memo = dp_memo[pos][tightLow][tightHigh][sum];
    if (memo != -1) return memo;
    int low_d = tightLow ? ld[pos] : 0;
    int high_d = tightHigh ? hd[pos] : 9;
    for (int d = low_d; d <= high_d; ++d) {
        bool nLow = tightLow && (d == ld[pos]);
        bool nHigh = tightHigh && (d == hd[pos]);
        if (dfs(pos + 1, nLow, nHigh, sum + d)) {
            return memo = 1;
        }
    }
    return memo = 0;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read inputs
    A = inf.readLong(1LL, 999999999999999LL, "A");
    inf.readSpace();
    B = inf.readLong(1LL, 999999999999999LL, "B");
    inf.readSpace();
    S = inf.readInt(1, 135, "S");
    inf.readEoln();

    ensuref(A <= B, "A (%lld) must be <= B (%lld)", A, B);

    // Prepare digit arrays for DP: pad to same length
    string sa = to_string(A);
    string sb = to_string(B);
    L = max(sa.size(), sb.size());
    // pad with leading zeros
    while ((int)sa.size() < L) sa = "0" + sa;
    while ((int)sb.size() < L) sb = "0" + sb;
    ld.resize(L);
    hd.resize(L);
    for (int i = 0; i < L; ++i) {
        ld[i] = sa[i] - '0';
        hd[i] = sb[i] - '0';
    }

    // init memo
    memset(dp_memo, -1, sizeof(dp_memo));
    bool exists = dfs(0, true, true, 0);
    ensuref(exists,
            "No number in [%lld, %lld] has digit sum %d",
            A, B, S);

    inf.readEof();
    return 0;
}
