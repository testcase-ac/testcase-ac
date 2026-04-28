#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll LIM = 1, cur = 1, ans = -1;
int P;
set<pii> vis;

void dfs(int i) {
  if (vis.count({cur, i})) return;
  vis.insert({cur, i});

  if (i == P) {
    ans = max(ans, cur);
  }
  else {
    for (int d = 2; d <= 9; ++d) {
      if (cur * d >= LIM) continue;
      cur *= d;
      dfs(i + 1);
      cur /= d;
    }
  }
}

void solve() {
  int D; cin >> D >> P;
  for (int i = 0; i < D; ++i) LIM *= 10;

  dfs(0);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
