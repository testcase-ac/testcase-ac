#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 1e9 + 7;

void solve() {
  ll N, K; cin >> N >> K;

  ll deg = N - 1;
  while (K--) {
    N = N * deg % MOD;
    N = N * 500000004 % MOD;
    deg = (deg + MOD - 1) % MOD;
    deg = 2 * deg % MOD;
  }
  cout << N << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
