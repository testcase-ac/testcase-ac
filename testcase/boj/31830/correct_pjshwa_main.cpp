#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5, MOD = 26;
int A[MAXN + 10];

class LazySeg {

public:
  LazySeg(int N, int mod) {
    this->n = N; this->mod = mod;
    for (flag = 1; flag < N; flag <<= 1);
    tree.resize(2 * flag);
    lazy.resize(2 * flag);
  }

  void update(int L, int R, ll val) {
    __update_range(0, 0, n - 1, L, R, val);
  }

  ll query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n, flag, mod = 0;
  vector<ll> tree, lazy;

  void __update_lazy(int si, int ss, int se) {
    if (lazy[si] != 0) {
      tree[si] += (se - ss + 1) * lazy[si];
      if (mod) tree[si] %= mod;

      if (ss != se) {
        lazy[si * 2 + 1] += lazy[si];
        lazy[si * 2 + 2] += lazy[si];
        if (mod) {
          lazy[si * 2 + 1] %= mod;
          lazy[si * 2 + 2] %= mod;
        }
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

    if (mod) tree[si] = (tree[si * 2 + 1] % mod + tree[si * 2 + 2] % mod) % mod;
    else tree[si] = tree[si * 2 + 1] + tree[si * 2 + 2];
  }

  ll __query(int ss, int se, int qs, int qe, int si) {
    __update_lazy(si, ss, se);

    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    if (mod) return (__query(ss, mid, qs, qe, 2 * si + 1) % mod + __query(mid + 1, se, qs, qe, 2 * si + 2) % mod) % mod;
    else return __query(ss, mid, qs, qe, 2 * si + 1) + __query(mid + 1, se, qs, qe, 2 * si + 2);
  }
};

void solve() {
  int N, Q; cin >> N >> Q;
  LazySeg U(N + 1, MOD), D(N + 1, 0);

  string S; cin >> S;
  for (int i = 1; i <= N; ++i) {
    A[i] = S[i - 1] - 'A';
    U.update(i, i, A[i]);
    if (i > 1) D.update(i, i, A[i] != A[i - 1]);
  }

  auto print = [&]() {
  for (int i = 1; i <= N; ++i) {
    cout << (char)(U.query(i, i) + 'A') << ' ';
  } cout << '\n';
  for (int i = 1; i <= N; ++i) {
    cout << D.query(i, i) << ' ';
  } cout << '\n';
  };

  while (Q--) {
    int op, l, r; cin >> op >> l >> r;
    if (op == 1) {
      cout << D.query(l + 1, r) + 1 << '\n'; 
    }
    else {
      if (l > 1 && U.query(l, l) != U.query(l - 1, l - 1)) D.update(l, l, -1);
      if (r < N && U.query(r, r) != U.query(r + 1, r + 1)) D.update(r + 1, r + 1, -1);

      U.update(l, r, 1);

      if (l > 1 && U.query(l, l) != U.query(l - 1, l - 1)) D.update(l, l, 1);
      if (r < N && U.query(r, r) != U.query(r + 1, r + 1)) D.update(r + 1, r + 1, 1);
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
