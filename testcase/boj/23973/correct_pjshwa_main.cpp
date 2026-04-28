#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2500;
char board[MAX + 1][MAX + 1];

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> board[i];

  vector<pii> ones;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (board[i][j] == '1') ones.push_back({i, j});
  }

  for (auto [i, j] : ones) {
    int t[11];
    memset(t, 0, sizeof(t));

    for (int di = -9; di <= 9; di++) for (int dj = -9; dj <= 9; dj++) {
      int ni = i + di, nj = j + dj;
      if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;

      int score = 10 - max(abs(di), abs(dj));
      if (board[ni][nj] == '1') t[score]++;
    }

    bool able = true;
    for (int i = 1; i <= 10; i++) able &= (t[i] == 1);
    if (able) return cout << i << ' ' << j << '\n', void();
  }

  cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
