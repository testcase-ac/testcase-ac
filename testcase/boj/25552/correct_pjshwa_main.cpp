#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000;
char oboard[MAX + 1][MAX + 1], tboard[MAX + 1][MAX + 1];
bool vis[MAX + 1][MAX + 1];

void solve() {
  int N, M, D;
  cin >> N >> M;
  for (int i = 0; i < N; i++) cin >> oboard[i];
  cin >> D;
  for (int i = 0; i < N; i++) cin >> tboard[i];

  queue<pii> q;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    if (oboard[i][j] == 'O') q.push({i, j}), vis[i][j] = true;
  }

  while (!q.empty()) {
    auto [i, j] = q.front(); q.pop();

    for (int ni = i - D; ni <= i + D; ni++) {
      if (ni < 0 || ni >= N) continue;

      for (int nj = j - D + abs(ni - i); nj <= j + D - abs(ni - i); nj++) {
        if (nj < 0 || nj >= M) continue;
        if (vis[ni][nj]) continue;
        if (tboard[ni][nj] == 'X') continue;

        q.push({ni, nj});
        vis[ni][nj] = true;
      }
    }
  }

  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    if (tboard[i][j] == 'O' && !vis[i][j]) return cout << "NO\n", void();
    if (tboard[i][j] == 'X' && oboard[i][j] == 'O') return cout << "NO\n", void();
  }
  cout << "YES\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
