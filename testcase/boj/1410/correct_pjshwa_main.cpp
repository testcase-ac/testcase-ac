#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 15, MAXC = 50, MOD = 1e6 + 3;
int C[MAXC + 1][MAXC + 1];
string A[MAXN];

void solve() {
  int N, K; cin >> N >> K;
  for (int i = 0; i < N; ++i) cin >> A[i];
  int Z = A[0].size();

  int ans = 0;
  for (int s = 0; s < (1 << N); ++s) {
    int bcnt = __builtin_popcount(s);
    if (bcnt < K) continue;

    string U(Z, '?'); bool f = true;
    for (int i = 0; i < N; ++i) {
      if (!(s & (1 << i))) continue;
      for (int j = 0; j < Z; ++j) {
        if (A[i][j] == '?') continue;
        if (U[j] == '?') U[j] = A[i][j];
        else if (U[j] != A[i][j]) { f = false; break; }
      }
    }
    if (!f) continue;

    ll val = 1;
    for (int i = 0; i < Z; ++i) {
      if (U[i] == '?') val = (val * 26) % MOD;
    }

    if (bcnt == K) ans = (ans + val) % MOD;
    else {
      int add = val * C[bcnt][K] % MOD;
      if ((K - bcnt) & 1) add = MOD - add;
      ans = (ans + add) % MOD;
    }
  }
  cout << ans << '\n';

}

int main() {
  fast_io();

  C[0][0] = 1;
  for (int i = 1; i <= MAXC; ++i) {
    C[i][0] = 1;
    for (int j = 1; j <= i; ++j) {
      C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
    }
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
