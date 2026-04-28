#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll N, K; cin >> N >> K;

  ll C[50], L[50]; C[0] = L[0] = 1;
  for (int i = 1; i < 50; i++) {
    C[i] = C[i - 1] * 2;
    L[i] = L[i - 1] * 2 + 1;
  }

  for (int t = 1; t < K; t++) {
    for (int i = 0; i < 50; i++) {
      if (C[i] == 1) continue;
      C[i] /= 2;
    }
  }

  ll ans = 0;
  for (int i = 0; i < 50; i++) {
    ll e = L[i], s = L[i] - C[i] + 1;
    if (s > N) break;
    else if (e <= N) ans += C[i];
    else ans += N - s + 1;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
