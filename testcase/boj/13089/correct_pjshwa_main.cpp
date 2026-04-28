#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define compress(x) sort(all(x)), (x).erase(unique(all(x)), (x).end())
#define getidx(v, x) (lower_bound(all(v), x) - v.begin())
typedef long long ll;
using namespace std;

ll tree[1 << 19], lazy[1 << 19];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

class LazySegMax {

public:
  LazySegMax(int N) {
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
      tree[si] = max(tree[si], lazy[si]);

      if (ss != se) {
        lazy[si * 2 + 1] = max(lazy[si * 2 + 1], lazy[si]);
        lazy[si * 2 + 2] = max(lazy[si * 2 + 2], lazy[si]);
      }
      lazy[si] = 0;
    }
  }

  void __update_range(int si, int ss, int se, int us, int ue, ll val) {
    __update_lazy(si, ss, se);

    if (ss > se || ss > ue || se < us) return;

    if (ss >= us && se <= ue) {
      lazy[si] = max(lazy[si], val);
      __update_lazy(si, ss, se);
      return;
    }

    int mid = (ss + se) / 2;
    __update_range(si * 2 + 1, ss, mid, us, ue, val);
    __update_range(si * 2 + 2, mid + 1, se, us, ue, val);

    tree[si] = max(tree[si * 2 + 1], tree[si * 2 + 2]);
  }

  ll __query(int ss, int se, int qs, int qe, int si) {
    __update_lazy(si, ss, se);

    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return max(__query(ss, mid, qs, qe, 2 * si + 1), __query(mid + 1, se, qs, qe, 2 * si + 2));
  }
};

int main() {
  fast_io();

  int n, k, t;
  cin >> n >> k >> t;
  vector<tuple<int, int, int>> updates;

  while (t--) {
    int li, ri, xi;
    cin >> li >> ri >> xi;
    updates.emplace_back(xi, li, ri);
  }

  LazySegMax s(cpoints.size());
  for (auto [x, y] : updates) {
    int xi = getidx(cpoints, x);
    int yi = getidx(cpoints, y);
    s.update(xi, yi, s.query(xi, yi) + 1);
  }

  cout << s.query(0, cpoints.size() - 1) << '\n';
}
