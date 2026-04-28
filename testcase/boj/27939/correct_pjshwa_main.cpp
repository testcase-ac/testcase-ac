#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n; cin >> n;
  string A[n];
  for (int i = 0; i < n; i++) cin >> A[i];

  int m, k; cin >> m >> k;
  while (m--) {
    int b = 1;
    for (int i = 0; i < k; i++) {
      int x; cin >> x;
      b &= A[x - 1] == "W";
    }
    if (b) return cout << "W", void();
  }
  cout << "P";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
