#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int W, S, X, Y; cin >> W >> S >> X >> Y;

  vector<vector<int>> A;
  while (W--) {
    vector<int> a(X);
    for (auto &x : a) cin >> x;
    A.push_back(a);
  }

  vector<int> P(X);
  while (S--) {
    for (int i = 0; i < X; i++) {
      int p; cin >> p;
      P[i] = max(P[i], p);
    }
  }

  for (auto& v : A) {
    for (int i = 0; i < X; ++i) cout << min(v[i], Y - P[i]) << ' ';
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
