#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1 << 19;
const ll INF = 1e18;
ll tree[MAX], lazy[MAX];

class LazySegMin {

public:
  LazySegMin(int N) {
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
      tree[si] += lazy[si];

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

    tree[si] = min(tree[si * 2 + 1], tree[si * 2 + 2]);
  }

  ll __query(int ss, int se, int qs, int qe, int si) {
    __update_lazy(si, ss, se);

    if (ss > se || ss > qe || se < qs) return INF;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return min(__query(ss, mid, qs, qe, 2 * si + 1), __query(mid + 1, se, qs, qe, 2 * si + 2));
  }
};

void solve() {
  string s; int n, q;
  cin >> n >> s >> q;

  LazySegMin seg(n);

  int pf = 0;
  for (int i = 0; i < n; i++) {
    if (s[i] == '(') pf++;
    else pf--;
    seg.update(i, i, pf);
  }

  while (q--) {
    int x, y;
    cin >> x >> y;
    x--; y--;

    int sum;
    if (x == 0) sum = seg.query(y, y);
    else sum = seg.query(y, y) - seg.query(x - 1, x - 1);

    int pre;
    if (x == 0) pre = 0;
    else pre = seg.query(x - 1, x - 1);

    cout << (seg.query(x, y) == pre && sum == 0) << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
