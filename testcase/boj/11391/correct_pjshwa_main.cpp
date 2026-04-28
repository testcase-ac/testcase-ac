#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, K; cin >> N >> K;

  int u = 0;
  for (int i = 0; i < (1 << K); i++) {
    for (int j = 0; j < (1 << (N - K - 1)); j++) {
      cout << u << ' ' << (1 << N) - 1 - u << ' ';
      u++;
    }
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
