#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2000, MOD = 1e9 + 7;
int C[MAX + 1][MAX + 1];

void solve() {
  int N, K;
  cin >> N >> K;
  for (int i = 0; i <= N; i++) C[i][0] = 1;
  for (int i = 1; i <= N; i++) for (int j = 1; j <= K; j++) {
    C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
  }

  ll ans = C[N][K];
  for (int i = 0; i < K - 1; i++) ans = (ans * 2) % MOD;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
