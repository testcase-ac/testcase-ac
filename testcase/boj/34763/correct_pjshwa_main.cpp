#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, K; cin >> N >> K;
  for (int f = 1; f * f <= K; ++f) {
    if (K % f) continue;
    if (f + K / f == N + 1) return cout << "YES\n", void();
  }
  cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
