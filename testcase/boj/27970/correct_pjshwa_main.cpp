#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 1e9 + 7;

void solve() {
  string S; cin >> S;

  ll b = 1, N = S.size(), ans = 0;
  for (int i = 0; i < N; i++) {
    if (S[i] == 'O') ans = (ans + b) % MOD;
    b = (b * 2) % MOD;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
