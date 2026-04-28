#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int n, g;
map<int, int> D[4];

void solve() {
  for (int i = 0; i < 4; ++i) D[i].clear();

  while (g--) {
    int k, xs, ys, s, t; cin >> k >> xs >> ys >> s >> t;
    for (int j = 0; j < k; ++j) {
      int x = xs + j * s, y = ys + j * t;
      ++D[0][x]; ++D[1][y]; ++D[2][x - y]; ++D[3][x + y];
    }
  }

  int ans = 0;
  for (int i = 0; i < 4; ++i) for (auto& [_, y] : D[i]) ans += max(0, y - 1);
  cout << ans << '\n';
}

int main() {
  fast_io();

  while (cin >> n) {
    if (n == 0) break;
    cin >> g; solve();
  }
}
