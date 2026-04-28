#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int tree[1 << 21];

class SegmentTree {

public:
  SegmentTree(int N) {
    n = N;
    init(0, N - 1, 0);
  }

  void inc(int P) {
    __add(0, 0, n - 1, P, 1);
  }

  ll query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

  void init(int ss, int se, int si) {
    if (ss > se) return;

    if (ss == se) {
      tree[si] = 0;
      return;
    }

    int mid = (ss + se) / 2;
    init(ss, mid, si * 2 + 1);
    init(mid + 1, se, si * 2 + 2);

    tree[si] = tree[si * 2 + 1] + tree[si * 2 + 2];
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
    return __query(ss, mid, qs, qe, 2 * si + 1) + __query(mid + 1, se, qs, qe, 2 * si + 2);
  }

};

int main() {
  fast_io();

  int n;
  cin >> n;
  map<int, vector<int>> m;
  vector<int> q(n);
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    m[x].push_back(i);
  }
  for (int i = 0; i < n; i++) cin >> q[i];

  vector<int> a(n), b(n);
  SegmentTree s(1'000'001);

  for (auto [k, vv] : m) {
    for (int ix : vv) a[ix] = s.query(0, q[ix] - 1);
    for (int ix : vv) s.inc(q[ix]);
  }

  memset(tree, 0, sizeof(tree));
  for (auto iter = m.rbegin(); iter != m.rend(); ++iter) {
    auto [k, vv] = *iter;
    for (int ix : vv) b[ix] = s.query(q[ix] + 1, 1'000'000);
    for (int ix : vv) s.inc(q[ix]);
  }

  ll ans = 0;
  for (int i = 0; i < n; i++) ans += (ll)a[i] * b[i];
  cout << ans << '\n';
}
