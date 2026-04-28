#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll upto(ll n) {
  return n * (n + 1) / 2;
}

void solve() {
  int n, m, k;
  cin >> n >> m >> k;

  vector<vector<int>> quests(m, vector<int>(k));
  for (int i = 0; i < m; i++) for (int j = 0; j < k; j++) cin >> quests[i][j];

  int ans = 0;
  for (int i = 0; i < (1 << (2 * n)); i++) {
    if (__builtin_popcount(i) == n) {
      int cur = 0;
      for (int j = 0; j < m; j++) {
        bool a = true;
        for (int q : quests[j]) {
          if (i & (1 << (q - 1))) continue;
          a = false;
          break;
        }
        if (a) cur++;
      }
      if (cur > ans) ans = cur;
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
