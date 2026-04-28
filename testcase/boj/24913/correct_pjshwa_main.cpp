#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX = 1 << 18;
const ll INF = 1e18;
ll tree[MAX], tmax[MAX];

class SegmentTree {

public:
  SegmentTree(int N) {
    n = N;
  }

  void add(int P, int val) {
    __add(0, 0, n - 1, P, val);
  }

  ll query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n;

  void __add(int si, int ss, int se, int p, int val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      tree[si] += val;
      return;
    }

    int mid = (ss + se) / 2;
    __add(si * 2 + 1, ss, mid, p, val);
    __add(si * 2 + 2, mid + 1, se, p, val);

    tree[si] = tree[si * 2 + 1] + tree[si * 2 + 2];
  }

  ll __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return __query(ss, mid, qs, qe, 2 * si + 1) + __query(mid + 1, se, qs, qe, 2 * si + 2);
  }

};


class SegmentTreeMax {

public:
  SegmentTreeMax(int N) {
    n = N;
  }

  void add(int P, int val) {
    __add(0, 0, n - 1, P, val);
  }

  int query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n;

  void __add(int si, int ss, int se, int p, int val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      tmax[si] += val;
      return;
    }

    int mid = (ss + se) / 2;
    __add(si * 2 + 1, ss, mid, p, val);
    __add(si * 2 + 2, mid + 1, se, p, val);

    tmax[si] = max(tmax[si * 2 + 1], tmax[si * 2 + 2]);
  }

  ll __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return -INF;
    if (ss >= qs && se <= qe) return tmax[si];

    int mid = (ss + se) / 2;
    return max(__query(ss, mid, qs, qe, si * 2 + 1), __query(mid + 1, se, qs, qe, si * 2 + 2));
  }
};


void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, q;
  cin >> n >> q;
  SegmentTree st(n + 10);
  SegmentTreeMax sx(n + 10);

  while (q--) {
    int op, x, y;
    cin >> op >> x >> y;

    if (op == 1) st.add(y, x), sx.add(y, x);
    if (op == 2) {
      ll cc = st.query(n + 1, n + 1);
      ll cs = st.query(1, n);
      ll cx = sx.query(1, n);
      ll target = (cc + x - 1) * n;

      if (cx < cc + x && cs + y <= target) cout << "YES\n";
      else cout << "NO\n";
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
