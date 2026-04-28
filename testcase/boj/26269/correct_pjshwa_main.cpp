#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll N, K, X; cin >> N >> K >> X;
  if (K < 2 * N - 1) return cout << "-1\n", void();

  // The sequence always looks like a stair of length (K - 1) / 2
  // with exactly (N - 1) elevations
  bool o = K % 2;
  K = (K - 1) / 2;
  X--;

  vector<int> ans{1};
  int p = 1;
  for (int i = 1; i <= K; i++) {
    // Can I elevate here?
    if (p < N) {
      int n = K - i, c = N - p;
      if (c > n - c) c = n - c;

      // If X >= C, we should elevate
      __int128_t C = 1;
      if (n < 0 || c < 0 || c > n) C = 0;
      int o = C <= X;

      // C does not decrease in this loop
      for (int j = 1; C > 0 && j <= c; j++) {
        C *= n - j + 1;
        C /= j;
        if (C > X) {
          o = 0;
          break;
        }
      }

      if (o) p++, X -= C;
    }

    ans.push_back(p);
  }
  if (X) return cout << "-1\n", void();

  for (int i = 0; i < K + 1; i++) cout << ans[i] << ' ';
  for (int i = o; i < K + 1; i++) cout << ans[K - i] << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
