#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  map<string, vector<string>> G;
  for (int i = 0; i < N; ++i) {
    string pi, si; cin >> pi >> si;
    if (si == "-") continue;
    G[si].push_back(pi);
  }

  int ans = 0;
  for (auto& [_, v] : G) {
    if (v.size() == 2) ++ans;
  }
  cout << ans << '\n';
  for (auto& [_, v] : G) {
    if (v.size() == 2) cout << v[0] << ' ' << v[1] << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
