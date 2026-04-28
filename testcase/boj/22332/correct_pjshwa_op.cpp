#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2000;
int B[MAX + 1][MAX + 1];

void solve() {
  int N; cin >> N;

  vector<tuple<int, int, int, int>> ans;
  for (int i = 1; i <= N; ++i) for (int j = 1; j <= N; ++j) {
    int x; cin >> x;
    if (x == 1) ans.emplace_back(j, j, i, i);
  }

  cout << ans.size() << '\n';
  for (auto [y1, y2, x1, x2] : ans) {
    cout << y1 << ' ' << y2 << ' ' << x1 << ' ' << x2 << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
