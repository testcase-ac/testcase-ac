#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, D; cin >> N >> D;

  int ok = 1;
  for (int i = 0; i < N; ++i) {
    int x, a, g, r; cin >> x >> a >> g >> r;
    if (x < a) ok = 0;
    else {
      x -= a;
      x %= g + r;
      if (x > g) ok = 0;
    }
  }

  if (ok) cout << "YES\n";
  else cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
