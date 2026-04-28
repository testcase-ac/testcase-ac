#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int V = 999, E = 1501;
  cout << V << ' ' << E << '\n';

  int cnt = 0;
  for (int i = 0; i < V; ++i) for (int j = i + 1; j < V; ++j) {
    if (cnt >= E) break;
    cout << i << ' ' << j << '\n';
    ++cnt;
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
