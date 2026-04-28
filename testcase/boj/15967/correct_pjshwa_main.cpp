#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX = 1e6;
ll tree[1 << 21], lazy[1 << 21];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

class LazySeg {

public:
  LazySeg(int N) {
    n = N;
  }

  void update(int L, int R, ll val) {
    __update_range(0, 0, n - 1, L, R, val);
  }

  ll query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n;

  void __update_lazy(int si, int ss, int se) {
    if (lazy[si] != 0) {
      tree[si] += (se - ss + 1) * lazy[si];

      if (ss != se) {
        lazy[si * 2 + 1] += lazy[si];
        lazy[si * 2 + 2] += lazy[si];
      }
      lazy[si] = 0;
    }
  }

  void __update_range(int si, int ss, int se, int us, int ue, ll val) {
    __update_lazy(si, ss, se);

    if (ss > se || ss > ue || se < us) return;

    if (ss >= us && se <= ue) {
      lazy[si] = val;
      __update_lazy(si, ss, se);
      return;
    }

    int mid = (ss + se) / 2;
    __update_range(si * 2 + 1, ss, mid, us, ue, val);
    __update_range(si * 2 + 2, mid + 1, se, us, ue, val);

    tree[si] = tree[si * 2 + 1] + tree[si * 2 + 2];
  }

  ll __query(int ss, int se, int qs, int qe, int si) {
    __update_lazy(si, ss, se);

    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return __query(ss, mid, qs, qe, 2 * si + 1) + __query(mid + 1, se, qs, qe, 2 * si + 2);
  }
};

int main() {
  fast_io();

  int n, q1, q2;
  cin >> n >> q1 >> q2;
  q1 += q2;

  LazySeg seg(n + 1);
  for (int i = 1; i <= n; i++) {
    int x;
    cin >> x;
    seg.update(i, i, x);
  }

  while (q1--) {
    int op;
    cin >> op;
    if (op == 1) {
      int l, r;
      cin >> l >> r;
      cout << seg.query(l, r) << '\n';
    }
    if (op == 2) {
      int l, r, x;
      cin >> l >> r >> x;
      seg.update(l, r, x);
    }
  }
}
