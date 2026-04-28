#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX = 1 << 19, INF = 1e9 + 7;
int a[MAX], inv[MAX];

class SegmentTreeMin {

public:
  SegmentTreeMin(int N) {
    n = N;
    for (flag = 1; flag < N; flag <<= 1);
    tmin.resize(2 * flag);
  }

  void update(int P, int val) {
    __update(0, 0, n - 1, P, val);
  }

  int query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n, flag;
  vector<int> tmin;

  void __update(int si, int ss, int se, int p, int val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      tmin[si] = val;
      return;
    }

    int mid = (ss + se) / 2;
    __update(si * 2 + 1, ss, mid, p, val);
    __update(si * 2 + 2, mid + 1, se, p, val);

    tmin[si] = min(tmin[si * 2 + 1], tmin[si * 2 + 2]);
  }

  int __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return INF;
    if (ss >= qs && se <= qe) return tmin[si];

    int mid = (ss + se) / 2;
    return min(__query(ss, mid, qs, qe, si * 2 + 1), __query(mid + 1, se, qs, qe, si * 2 + 2));
  }
};


class SegmentTreeMax {

public:
  SegmentTreeMax(int N) {
    n = N;
    for (flag = 1; flag < N; flag <<= 1);
    tmax.resize(2 * flag);
  }

  void update(int P, int val) {
    __update(0, 0, n - 1, P, val);
  }

  int query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n, flag;
  vector<int> tmax;

  void __update(int si, int ss, int se, int p, int val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      tmax[si] = val;
      return;
    }

    int mid = (ss + se) / 2;
    __update(si * 2 + 1, ss, mid, p, val);
    __update(si * 2 + 2, mid + 1, se, p, val);

    tmax[si] = max(tmax[si * 2 + 1], tmax[si * 2 + 2]);
  }

  int __query(int ss, int se, int qs, int qe, int si) {
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

  SegmentTreeMin sm(n + 1), pm(n + 1);
  SegmentTreeMax sx(n + 1), px(n + 1);

  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    sm.update(i, a[i]); sx.update(i, a[i]);
    pm.update(a[i], i); px.update(a[i], i);
  }

  while (q--) {
    int op, x, y;
    cin >> op >> x >> y;

    if (op == 1) {
      swap(a[x], a[y]);
      sm.update(x, a[x]); sm.update(y, a[y]);
      sx.update(x, a[x]); sx.update(y, a[y]);
      pm.update(a[x], x); pm.update(a[y], y);
      px.update(a[x], x); px.update(a[y], y);
    }
    if (op == 2) {
      int l = pm.query(x, y), r = px.query(x, y);
      if (sm.query(l, r) == x && sx.query(l, r) == y) cout << "YES\n";
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
