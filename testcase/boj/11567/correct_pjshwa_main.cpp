#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

const int MAX = 500;
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};
char board[MAX + 1][MAX + 1];
bool vis[MAX][MAX];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; ++i) cin >> board[i];

  int si, sj, ei, ej;
  cin >> si >> sj >> ei >> ej;
  si--; sj--; ei--; ej--;

  queue<pair<int, int>> q;
  q.push({si, sj});
  vis[si][sj] = true;

  while (!q.empty()) {
    auto [i, j] = q.front();
    q.pop();

    for (int k = 0; k < 4; ++k) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
      if (ni == ei && nj == ej) {
        if (board[ei][ej] == '.') {
          q.push({ei, ej});
          board[ei][ej] = 'X';
          vis[ei][ej] = true;
        }
        else return cout << "YES\n", void();
      }
      else if (board[ni][nj] == '.' && !vis[ni][nj]) {
        q.push({ni, nj});
        vis[ni][nj] = true;
      }
    }
  }

  cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
