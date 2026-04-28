#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAX = 2e5, MOD = 1e9 + 7;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

class LazySeg {

public:
  LazySeg(int N) {
    n = N;
    for (flag = 1; flag < N; flag <<= 1);
    tree.resize(2 * flag);
    lazy.resize(2 * flag, -1);
  }

  void assign(int L, int R, ll val) {
    __assign_range(0, 0, n - 1, L, R, val);
  }

  ll query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n, flag;
  vector<ll> tree, lazy;

  void __update_lazy(int si, int ss, int se) {
    if (lazy[si] != -1) {
      tree[si] = (ll)(se - ss + 1) * lazy[si] % MOD;

      if (ss != se) {
        lazy[si * 2 + 1] = lazy[si];
        lazy[si * 2 + 2] = lazy[si];
      }
      lazy[si] = -1;
    }
  }

  void __assign_range(int si, int ss, int se, int us, int ue, ll val) {
    __update_lazy(si, ss, se);

    if (ss > se || ss > ue || se < us) return;

    if (ss >= us && se <= ue) {
      lazy[si] = val;
      __update_lazy(si, ss, se);
      return;
    }

    int mid = (ss + se) / 2;
    __assign_range(si * 2 + 1, ss, mid, us, ue, val);
    __assign_range(si * 2 + 2, mid + 1, se, us, ue, val);

    tree[si] = (tree[si * 2 + 1] + tree[si * 2 + 2]) % MOD;
  }

  ll __query(int ss, int se, int qs, int qe, int si) {
    __update_lazy(si, ss, se);

    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return (__query(ss, mid, qs, qe, 2 * si + 1) + __query(mid + 1, se, qs, qe, 2 * si + 2)) % MOD;
  }
};

void solve() {
  int N;
  cin >> N;

  vector<ll> B(N + 1);
  for (int i = 1; i <= N; i++) cin >> B[i];

  vector<ll> ans(N + 1, 0);
  ans[1] = (B[1] * B[1]) % MOD;
  stack<pii> sm, sx;
  LazySeg sms(N + 1), sxs(N + 1);

  sm.push({B[1], 1});
  sx.push({B[1], 1});
  sms.assign(1, 1, B[1]);
  sxs.assign(1, 1, B[1]);

  for (int i = 2; i <= N; i++) {
    int wx = 1, wm = 1;
    while (!sx.empty()) {
      auto [v, c] = sx.top();
      if (v > B[i]) break;
      wx += c;
      sx.pop();
    }
    while (!sm.empty()) {
      auto [v, c] = sm.top();
      if (v < B[i]) break;
      wm += c;
      sm.pop();
    }
    sx.push({B[i], wx});
    sm.push({B[i], wm});

    if (wx > 1) {
      sxs.assign(i - wx + 1, i, B[i]);
      sms.assign(i, i, B[i]);

      ans[i] = (ans[i] + sms.query(i - wx + 1, i) * B[i]) % MOD;
      ans[i] = (ans[i] + ans[i - wx + 1] - (B[i - wx + 1] * B[i - wx + 1] % MOD) + MOD) % MOD;
    }
    else {
      sms.assign(i - wm + 1, i, B[i]);
      sxs.assign(i, i, B[i]);

      ans[i] = (ans[i] + sxs.query(i - wm + 1, i) * B[i]) % MOD;
      ans[i] = (ans[i] + ans[i - wm + 1] - (B[i - wm + 1] * B[i - wm + 1] % MOD) + MOD) % MOD;
    }
  }

  ll ret = 0;
  for (int i = 1; i <= N; i++) ret = (ret + ans[i]) % MOD, cout << ans[i] << endl;
  cout << ret << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
