#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class TreeNode {
public:
  int lmin, rmax, vall;
};

const int MAX = 3e5, MOD = 1e9 + 7, INF = 1e9 + 7;
ll fac[MAX + 1], ifac[MAX + 1];
TreeNode tree[1 << 20];

ll C(int n, int k) {
  if (n < 0 || k < 0 || n < k) return 0;
  return fac[n] * ifac[k] % MOD * ifac[n - k] % MOD;
}

ll lpow(ll x, ll y, ll m) {
  ll r = 1;
  x %= m;
  while (y) {
    if (y & 1) r = (r * x) % m;
    x = (x * x) % m;
    y >>= 1;
  }
  return r;
}

class SegmentTree {

public:
  SegmentTree(int N) {
    n = N;
    __init(0, N - 1, 0);
  }

  void update(int P, int val) {
    __update(0, 0, n - 1, P, val);
  }

  TreeNode query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n;

  void __init(int ss, int se, int si) {
    if (ss > se) return;

    if (ss == se) {
      tree[si] = {0, 0, 0};
      return;
    }

    int mid = (ss + se) / 2;
    __init(ss, mid, si * 2 + 1);
    __init(mid + 1, se, si * 2 + 2);

    TreeNode l = tree[si * 2 + 1], r = tree[si * 2 + 2];
    tree[si].lmin = min(l.lmin, l.vall + r.lmin);
    tree[si].rmax = max(r.rmax, r.vall + l.rmax);
    tree[si].vall = l.vall + r.vall;
  }

  void __update(int si, int ss, int se, int p, int val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      tree[si] = {val, val, val};
      return;
    }

    int mid = (ss + se) / 2;
    __update(si * 2 + 1, ss, mid, p, val);
    __update(si * 2 + 2, mid + 1, se, p, val);

    TreeNode l = tree[si * 2 + 1], r = tree[si * 2 + 2];
    tree[si].lmin = min(l.lmin, l.vall + r.lmin);
    tree[si].rmax = max(r.rmax, r.vall + l.rmax);
    tree[si].vall = l.vall + r.vall;
  }

  TreeNode __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return {INF, -INF, 0};
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    TreeNode l = __query(ss, mid, qs, qe, si * 2 + 1), r = __query(mid + 1, se, qs, qe, si * 2 + 2), ans;
    ans.lmin = min(l.lmin, l.vall + r.lmin);
    ans.rmax = max(r.rmax, r.vall + l.rmax);
    ans.vall = l.vall + r.vall;
    return ans;
  }

};

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  fac[0] = ifac[0] = 1;
  for (int i = 1; i <= MAX; i++) fac[i] = fac[i - 1] * i % MOD;
  ifac[MAX] = lpow(fac[MAX], MOD - 2, MOD);
  for (int i = MAX - 1; i >= 1; i--) ifac[i] = ifac[i + 1] * (i + 1) % MOD;

  int n;
  cin >> n;
  SegmentTree s(n);

  string o;
  cin >> o;
  for (int i = 0; i < n; i++) s.update(i, o[i] == '(' ? 1 : -1);

  int q;
  cin >> q;
  while (q--) {
    int op;
    cin >> op;
    if (op == 1) {
      int k;
      cin >> k;
      s.update(k - 1, -s.query(k - 1, k - 1).vall);
    }
    if (op == 2) {
      int l, r;
      cin >> l >> r;

      auto ql = s.query(0, l - 2), qr = s.query(r, n - 1);
      if (ql.lmin >= 0 && qr.rmax <= 0) {
        int len = r - l + 1;
        int x = (len + ql.vall + qr.vall) / 2;
        int y = (len + ql.vall - qr.vall) / 2 + 1;
        cout << (C(len, x) - C(len, y) + MOD) % MOD << '\n';
      }
      else cout << "0\n";
    }
  }
  
}
