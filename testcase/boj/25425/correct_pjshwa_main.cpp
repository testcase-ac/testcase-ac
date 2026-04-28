#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  ll N, M, a, K;
  cin >> N >> M >> a >> K;

  ll mmax = min(N - 1, (a - K));
  ll mmin = (a - K - 1) / M + 1;
  cout << mmax + 1 << ' ' << mmin + 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
