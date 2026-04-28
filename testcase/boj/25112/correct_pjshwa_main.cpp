#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5, INF = 1e9 + 7;
int a[MAX];

class SegmentTree {

public:
  SegmentTree(int N) {
    n = N;
    for (flag = 1; flag < N; flag <<= 1);
    tree.resize(2 * flag);
    __init(0, N - 1, 0);
  }

  void update(int P, int val) {
    __update(0, 0, n - 1, P, val);
  }

  ll query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n, flag;
  vector<ll> tree;

  void __init(int ss, int se, int si) {
    if (ss > se) return;

    if (ss == se) {
      tree[si] = a[ss];
      return;
    }

    int mid = (ss + se) / 2;
    __init(ss, mid, si * 2 + 1);
    __init(mid + 1, se, si * 2 + 2);

    tree[si] = tree[si * 2 + 1] + tree[si * 2 + 2];
  }

  void __update(int si, int ss, int se, int p, int val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      tree[si] = val;
      return;
    }

    int mid = (ss + se) / 2;
    __update(si * 2 + 1, ss, mid, p, val);
    __update(si * 2 + 2, mid + 1, se, p, val);

    tree[si] = tree[si * 2 + 1] + tree[si * 2 + 2];
  }

  ll __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return __query(ss, mid, qs, qe, si * 2 + 1) + __query(mid + 1, se, qs, qe, si * 2 + 2);
  }
};

void solve() {
  int n, q;
  cin >> n;
  for (int i = 0; i < n - 1; i++) cin >> a[i];

  SegmentTree s(n - 1);
  cin >> q;

  int left = 0, right = n;
  while (left < right) {
    int mid = (left + right) / 2;
    if (s.query(0, mid) > s.query(mid + 1, n - 1)) right = mid;
    else left = mid + 1;
  }

  cout << min(
    abs(s.query(0, left) - s.query(left + 1, n - 1)),
    abs(s.query(0, left - 1) - s.query(left, n - 1))
  ) << '\n';

  while (q--) {
    int j, t;
    cin >> j >> t;
    s.update(j - 1, t);

    left = 0, right = n;
    while (left < right) {
      int mid = (left + right) / 2;
      if (s.query(0, mid) > s.query(mid + 1, n - 1)) right = mid;
      else left = mid + 1;
    }

    cout << min(
      abs(s.query(0, left) - s.query(left + 1, n - 1)),
      abs(s.query(0, left - 1) - s.query(left, n - 1))
    ) << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
