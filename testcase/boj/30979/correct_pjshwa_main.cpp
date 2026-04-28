#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int T, N; cin >> T >> N;

  int S = 0;
  for (int i = 0; i < N; ++i) {
    int x; cin >> x;
    S += x;
  }

  if (S >= T) cout << "Padaeng_i Happy\n";
  else cout << "Padaeng_i Cry\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
