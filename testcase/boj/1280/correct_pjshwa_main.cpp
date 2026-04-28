#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX = 2e5, MOD = 1e9 + 7;

class SegmentTree {

public:
  SegmentTree(int N) {
    n = N;
    for (flag = 1; flag < N; flag <<= 1);
    tree.resize(2 * flag);
  }

  void add(int P, int val) {
    __add(0, 0, n - 1, P, val);
  }

  int query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n, flag;
  vector<int> tree;

  void __add(int si, int ss, int se, int p, int val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      tree[si] = (tree[si] + val) % MOD;
      return;
    }

    int mid = (ss + se) / 2;
    __add(si * 2 + 1, ss, mid, p, val);
    __add(si * 2 + 2, mid + 1, se, p, val);

    tree[si] = (tree[si * 2 + 1] + tree[si * 2 + 2]) % MOD;
  }

  int __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return (__query(ss, mid, qs, qe, si * 2 + 1) + __query(mid + 1, se, qs, qe, si * 2 + 2)) % MOD;
  }
};

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int q;
  cin >> q;

  SegmentTree sv(MAX), sc(MAX);
  ll ans = 1;
  for (int i = 1; i <= q; i++) {
    int x;
    cin >> x;

    ll lc = sc.query(0, x - 1), rc = sc.query(x + 1, MAX);
    ll lv = sv.query(0, x - 1), rv = sv.query(x + 1, MAX);

    ll res = (rv - (rc * x) % MOD + MOD) % MOD;
    res = (res + lc * x - lv) % MOD;
    if (i >= 2) ans = (ans * res) % MOD;

    sv.add(x, x);
    sc.add(x, 1);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
