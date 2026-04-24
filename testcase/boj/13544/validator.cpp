#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int N, M;
vector<ll> A;
vector<vector<int>> seg;

// build merge sort tree
void build(int node, int l, int r) {
    if (l == r) {
        seg[node] = vector<int>(1, (int)A[l]);
    } else {
        int mid = (l + r) >> 1;
        build(node<<1, l, mid);
        build(node<<1|1, mid+1, r);
        auto &L = seg[node<<1];
        auto &R = seg[node<<1|1];
        seg[node].resize(L.size() + R.size());
        merge(L.begin(), L.end(), R.begin(), R.end(), seg[node].begin());
    }
}

// query count of elements > k in [ql, qr]
int query(int node, int l, int r, int ql, int qr, int k) {
    if (r < ql || l > qr) return 0;
    if (ql <= l && r <= qr) {
        auto &v = seg[node];
        // first element > k
        auto it = upper_bound(v.begin(), v.end(), k);
        return int(v.end() - it);
    }
    int mid = (l + r) >> 1;
    return query(node<<1, l, mid, ql, qr, k)
         + query(node<<1|1, mid+1, r, ql, qr, k);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N
    N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // A_i
    A.resize(N+1);
    {
        vector<ll> tmp = inf.readLongs(N, 1LL, 1000000000LL, "A_i");
        for (int i = 1; i <= N; i++) {
            A[i] = tmp[i-1];
        }
    }
    inf.readEoln();

    // M
    M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // build data structure
    seg.assign(4*(N+1), vector<int>());
    build(1, 1, N);

    // process queries and simulate last_ans
    ll last_ans = 0;
    for (int qi = 0; qi < M; qi++) {
        ll a = inf.readLong(0LL, 2000000000LL, "a_query");
        inf.readSpace();
        ll b = inf.readLong(0LL, 2000000000LL, "b_query");
        inf.readSpace();
        ll c = inf.readLong(0LL, 2000000000LL, "c_query");
        inf.readEoln();

        ll i = a ^ last_ans;
        ll j = b ^ last_ans;
        ll k = c ^ last_ans;

        ensuref(1 <= i && i <= j && j <= N,
                "After xor at query %d: got invalid range i=%lld, j=%lld, but N=%d",
                qi, i, j, N);
        ensuref(1 <= k && k <= 1000000000LL,
                "After xor at query %d: got invalid k=%lld", qi, k);

        // compute answer = count of A[p] > k for p in [i..j]
        last_ans = query(1, 1, N, (int)i, (int)j, (int)k);
    }

    inf.readEof();
    return 0;
}
