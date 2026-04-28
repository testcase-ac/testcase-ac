#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX = 1 << 22, INF = 1e9 + 7;
ll tree[MAX], lazy[MAX];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

class LazySeg {

public:
  LazySeg(int N) {
    n = N;
  }

  void update(int L, int R, int diff) {
    __updateRange(0, 0, n - 1, L, R, diff);
  }

  ll query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n;

  void updateLazy(int si, int ss, int se) {
    if (lazy[si] != 0) {
      tree[si] = tree[si] + lazy[si] * (se - ss + 1);

      if (ss != se) {
        lazy[si * 2 + 1] += lazy[si];
        lazy[si * 2 + 2] += lazy[si];
      }
      lazy[si] = 0;
    }
  }

  void __updateRange(int si, int ss, int se, int us, int ue, int diff) {
    updateLazy(si, ss, se);

    if (ss > se || ss > ue || se < us) return;

    if (ss >= us && se <= ue) {
      lazy[si] = diff;
      updateLazy(si, ss, se);
      return;
    }

    int mid = (ss + se) / 2;
    __updateRange(si * 2 + 1, ss, mid, us, ue, diff);
    __updateRange(si * 2 + 2, mid + 1, se, us, ue, diff);

    tree[si] = tree[si * 2 + 1] + tree[si * 2 + 2];
  }

  ll __query(int ss, int se, int qs, int qe, int si) {
    updateLazy(si, ss, se);

    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    ll lhs = __query(ss, mid, qs, qe, 2 * si + 1);
    ll rhs = __query(mid + 1, se, qs, qe, 2 * si + 2);
    return lhs + rhs;
  }

};

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;

  LazySeg s(n);
  set<pair<int, int>> regions;
  for (int i = 0; i < m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    regions.insert({a, i});
    s.update(i, i, c);
  }

  while (1) {
    int op, x, y, z;
    cin >> op;
    if (op == 1) {
      cin >> x >> y;
      auto sit = regions.upper_bound({x, INF}), eit = regions.upper_bound({y, INF});
      sit--; eit--;
      if (x > y) {
        if (sit == eit) cout << s.query(0, m - 1) << '\n';
        else cout << s.query(0, eit->second) + s.query(sit->second, m - 1) << '\n';
      }
      else cout << s.query(sit->second, eit->second) << '\n';
    }
    else if (op == 2) {
      cin >> x >> y >> z;
      auto sit = regions.upper_bound({x, INF}), eit = regions.upper_bound({y, INF});
      sit--; eit--;

      if (x > y) {
        if (sit == eit) s.update(0, m - 1, z);
        else {
          s.update(0, eit->second, z);
          s.update(sit->second, m - 1, z);
        }
      }
      else s.update(sit->second, eit->second, z);
    }
    else break;
  }
}
