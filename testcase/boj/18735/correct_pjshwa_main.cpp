#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n; cin >> n;
  if (n == 1) return cout << "1\n", void();

  map<int, vector<int>> t;
  for (int i = 0; i < n; i++) {
    int x; cin >> x;
    t[x].push_back(i);
  }

  int ans = 0;
  for (auto& [_, vv] : t) {
    if (vv.size() == 1) continue;

    int f = 0;
    for (int i = 1; i < vv.size(); i++) {
      if (vv[i] - vv[i - 1] <= 2) f = 1;
    }
    ans += f;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
