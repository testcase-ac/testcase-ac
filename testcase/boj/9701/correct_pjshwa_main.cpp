#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 1e9 + 7;
int tc;
int P[4];
int d[10][10][10][10], u[40];

int r(int p2, int p4, int p6, int p8) {
  int rem = p2 + p4 + p6 + p8;
  if (rem == 0) return 1;

  if (d[p2][p4][p6][p8] != -1) return d[p2][p4][p6][p8];

  int ret = 0;
  if (p2) ret = (ret + r(p2 - 1, p4, p6, p8)) % MOD;
  if (p4) ret = (ret + r(p2, p4 - 1, p6, p8)) % MOD;
  if (p6) ret = (ret + r(p2, p4, p6 - 1, p8)) % MOD;
  if (p8) ret = (ret + r(p2, p4, p6, p8 - 1)) % MOD;

  u[rem] = (u[rem] + ret) % MOD;
  return d[p2][p4][p6][p8] = ret;
}

void solve() {
  cout << "Case #" << ++tc << ": ";

  for (int i = 1; i <= 9; i++) {
    int x;
    cin >> x;
    if (i & 1) continue;
    P[i / 2 - 1] = x;
  }

  ll ans = 0;
  for (int i = 0; i < 4; i++) {
    if (P[i] == 0) continue;

    P[i]--;
    memset(d, -1, sizeof(d));
    memset(u, 0, sizeof(u));
    u[0] = 1;
    r(P[0], P[1], P[2], P[3]);

    ll pw = 2 * (i + 1);
    for (int si = 0; si < 40; si++) {
      ll cur = 0;
      for (int j = si; j < 40; j++) cur = (cur + u[j]) % MOD;
      cur = (cur * pw) % MOD;
      ans = (ans + cur) % MOD;
      pw = (pw * 10) % MOD;
    }

    P[i]++;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
