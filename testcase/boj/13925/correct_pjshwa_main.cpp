#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MAX = 1e5, MOD = 1e9 + 7;
int a[MAX];
ll tree[1 << 19];
pair<ll, ll> lazy[1 << 19];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

class LazySeg {

public:
  LazySeg(int N) {
    n = N;
    __init(0, n - 1, 0);
  }

  void update(int L, int R, pair<ll, ll> npair) {
    __updateRange(0, 0, n - 1, L, R, npair);
  }

  ll query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n;

  void __init(int ss, int se, int si) {
    if (ss > se) return;

    if (ss == se) { 
      tree[si] = a[ss];
      return;
    }

    int mid = (ss + se) / 2;
    __init(ss, mid, si * 2 + 1);
    __init(mid + 1, se, si * 2 + 2);

    tree[si] = (tree[si * 2 + 1] + tree[si * 2 + 2]) % MOD;
  }

  void updateLazy(int si, int ss, int se) {
    auto [m, a] = lazy[si];
    if (m == 1 && a == 0) return;
    tree[si] = (m * tree[si] + (se - ss + 1) * a) % MOD;

    ll pm, pa;
    if (ss != se) {
      tie(pm, pa) = lazy[si * 2 + 1];
      lazy[si * 2 + 1] = {(m * pm) % MOD, (m * pa + a) % MOD};
      tie(pm, pa) = lazy[si * 2 + 2];
      lazy[si * 2 + 2] = {(m * pm) % MOD, (m * pa + a) % MOD};
    }
    lazy[si] = {1, 0};
  }

  void __updateRange(int si, int ss, int se, int us, int ue, pair<ll, ll>& npair) {
    updateLazy(si, ss, se);

    if (ss > se || ss > ue || se < us) return;

    if (ss >= us && se <= ue) {
      auto [nm, na] = npair;
      auto [m, a] = lazy[si];
      lazy[si] = {(nm * m) % MOD, (nm * a + na) % MOD};
      updateLazy(si, ss, se);
      return;
    }

    int mid = (ss + se) / 2;
    __updateRange(si * 2 + 1, ss, mid, us, ue, npair);
    __updateRange(si * 2 + 2, mid + 1, se, us, ue, npair);

    tree[si] = (tree[si * 2 + 1] + tree[si * 2 + 2]) % MOD;
  }
    
  ll __query(int ss, int se, int qs, int qe, int si) {
    updateLazy(si, ss, se);

    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return (__query(ss, mid, qs, qe, 2 * si + 1) + __query(mid + 1, se, qs, qe, 2 * si + 2)) % MOD;
  }

};

int main() {
  fast_io();

  int n, q;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < (1 << 19); i++) lazy[i] = {1, 0};
  cin >> q;

  LazySeg s(n);
  while (q--) {
    int qi, x, y, v;
    cin >> qi >> x >> y;
    if (qi != 4) cin >> v;

    if (qi == 1) s.update(x - 1, y - 1, {1, v});
    if (qi == 2) s.update(x - 1, y - 1, {v, 0});
    if (qi == 3) s.update(x - 1, y - 1, {0, v});
    if (qi == 4) cout << s.query(x - 1, y - 1) << '\n';
  }
}
