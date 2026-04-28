#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100;
const int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
int board[MAX][MAX], vis[MAX][MAX][4];
int N, M;

bool oob(int x, int y) {return x < 0 || x >= N || y < 0 || y >= M;}

void solve() {
  cin >> N >> M;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) cin >> board[i][j];

  vector<int> ans;
  for (int i = 0; i < N; ++i) {
    int dir = 0, ci = i, cj = 0;
    memset(vis, 0, sizeof(vis));

    while (1) {
      if (vis[ci][cj][dir]) {
        ans.push_back(i + 1);
        break;
      }

      vis[ci][cj][dir] = 1;
      int mul = board[ci][cj];
      int ni = ci + mul * dx[dir], nj = cj + mul * dy[dir];
      if (oob(ni, nj)) break;

      ci = ni, cj = nj;
      dir = (dir + 1) % 4;
    }
  }

  cout << ans.size() << '\n';
  for (int e : ans) cout << e << ' ';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
