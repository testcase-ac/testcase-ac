#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n, m; cin >> n >> m;

  vector<tii> ops;
  ops.push_back({1, 1, -1});

  int c = 1;
  while (m--) {
    int x; cin >> x;
    ops.push_back({1, 1 + x, c++});
    ops.push_back({2, 0, 0});
  }

  cout << ops.size() << '\n';
  for (auto& [o, x, h] : ops) {
    if (o == 1) cout << "U " << x << ' ' << h << '\n';
    else cout << "P\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
