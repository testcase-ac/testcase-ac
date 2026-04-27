#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200000, "N");
    inf.readEoln();

    vector<long long> c(n);
    for (int i = 1; i <= n - 1; ++i) {
        c[i] = inf.readLong(1LL, 1000000000000000000LL, "c_i");
        if (i < n - 1) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    deque<int> q;
    vector<int> backStarts, backEnds;
    for (int i = 2; i <= n - 1; ++i) {
        long long diff = c[i] - c[i - 1];
        if (diff == 2) {
            backEnds.push_back(i);
        } else {
            q.push_back(i);
            if (diff == -2) {
                backStarts.push_back(i);
            }
        }
    }
    q.push_back(n);

    vector<int> p(n + 1, -1);
    p[1] = 1;
    int backIndex = 0;
    for (int pos = 2; pos <= n; ++pos) {
        if (backIndex < (int)backStarts.size() && p[pos - 1] == backStarts[backIndex]) {
            ensuref(backIndex < (int)backEnds.size(), "invalid crossing sequence: unmatched back edge at position %d", pos);
            p[pos] = backEnds[backIndex];
            ++backIndex;
        } else {
            ensuref(!q.empty(), "invalid crossing sequence: reconstruction queue is empty at position %d", pos);
            p[pos] = q.front();
            q.pop_front();
        }
    }
    ensuref(backIndex == (int)backStarts.size(), "invalid crossing sequence: %d unused back starts", (int)backStarts.size() - backIndex);
    ensuref(p[n] == n, "reconstructed path ends at %d, expected %d", p[n], n);

    vector<int> seen(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        ensuref(1 <= p[i] && p[i] <= n, "reconstructed vertex p_%d=%d is out of range", i, p[i]);
        ensuref(!seen[p[i]], "reconstructed vertex %d appears more than once", p[i]);
        seen[p[i]] = 1;
    }

    vector<long long> diff(n + 2, 0), got(n, 0);
    for (int i = 1; i < n; ++i) {
        int l = min(p[i], p[i + 1]);
        int r = max(p[i], p[i + 1]);
        ++diff[l];
        --diff[r];
    }
    long long cur = 0;
    for (int i = 1; i <= n - 1; ++i) {
        cur += diff[i];
        got[i] = cur;
        ensuref(got[i] == c[i], "edge %d has reconstructed count %lld, expected %lld", i, got[i], c[i]);
    }

    inf.readEof();
    return 0;
}
