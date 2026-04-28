#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

class SegmentTree {

public:
  SegmentTree(int N) {
    n = N;
    for (flag = 1; flag < N; flag <<= 1);
    tree.resize(2 * flag + 1);
  }

  void update(int P, int val) {
    __update(1, 0, n - 1, P, val);
  }

  int query(int L, int R, int x) {
    return __query(0, n - 1, L, R, 1, x);
  }

private:
  int n, flag;
  vector<int> tree;

  void __update(int si, int ss, int se, int p, int val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      tree[si] ^= val;
      return;
    }

    int mid = (ss + se) / 2;
    __update(si * 2, ss, mid, p, val);
    __update(si * 2 + 1, mid + 1, se, p, val);

    tree[si] = tree[si * 2] ^ tree[si * 2 + 1];
  }

  int __query(int ss, int se, int qs, int qe, int si, int x) {
    if (ss > se || ss > qe || se < qs) return 0;

    int cur = se - ss + 1;
    if (cur & x) si ^= 1;

    if (qs <= ss && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return __query(ss, mid, qs, qe, si * 2, x) ^ __query(mid + 1, se, qs, qe, si * 2 + 1, x);
  }
};

void solve() {
  int N, Q;
  cin >> N;

  SegmentTree s(1 << 19);
  for (int i = 0; i < N; i++) {
    int x;
    cin >> x;
    s.update(i, x);
  }

  cin >> Q;
  while (Q--) {
    int op;
    cin >> op;
    if (op == 1) {
      int l, r, x;
      cin >> l >> r >> x;
      cout << s.query(l, r, x) << '\n';
    }
    if (op == 2) {
      int i, x;
      cin >> i >> x;
      s.update(i, x);
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
