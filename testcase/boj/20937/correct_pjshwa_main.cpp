#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  map<int, int> t;
  for (int i = 0; i < N; i++) {
    int x; cin >> x;
    t[x]++;
  }

  int ans = 1;
  for (auto& [_, v] : t) ans = max(ans, v);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
