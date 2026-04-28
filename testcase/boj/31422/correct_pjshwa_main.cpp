#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5, MOD = 998244353;
int A[MAXN + 1];

ll nC2(ll n) {
  ll ret = n * (n - 1) % MOD;
  return ret * 499122177 % MOD;
}

void solve() {
  ll N; cin >> N;
  for (int i = 1; i <= N; ++i) cin >> A[i];

  ll ans_a = 0, ans_b = (1 << 30) - 1;
  ans_b = (ans_b * nC2(N + 1) % MOD);

  for (int j = 0; j < 30; ++j) {
    vector<int> streak_0_v, streak_1_v;
    int streak_0 = 0, streak_1 = 0;
    for (int i = 1; i <= N; ++i) {
      if (A[i] >> j & 1) {
        ++streak_1;
        if (streak_0) {
          streak_0_v.push_back(streak_0);
          streak_0 = 0;
        }
      }
      else {
        ++streak_0;
        if (streak_1) {
          streak_1_v.push_back(streak_1);
          streak_1 = 0;
        }
      }
    }
    if (streak_0) streak_0_v.push_back(streak_0);
    if (streak_1) streak_1_v.push_back(streak_1);

    for (int e : streak_0_v) {
      int add = nC2(e + 1) * (1 << j) % MOD;
      ans_b = (ans_b - add + MOD) % MOD;
    }
    for (int e : streak_1_v) {
      int add = nC2(e + 1) * (1 << j) % MOD;
      ans_a = (ans_a + add) % MOD;
    }
  }

  ll ans_c = 0;
  for (int j = 0; j < 30; ++j) {
    ll pcnt = 0, qcnt = 0, val = 1 << j;
    for (int i = 1; i <= N; ++i) {
      ++qcnt;
      if (A[i] >> j & 1) swap(pcnt, qcnt);
      ans_c = (ans_c + pcnt * val % MOD) % MOD;
    }
  }

  cout << ans_a << ' ' << ans_b << ' ' << ans_c << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
