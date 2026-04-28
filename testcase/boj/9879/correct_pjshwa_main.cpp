#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 500;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int board[MAX][MAX];
bool vis[MAX][MAX];
int n, m;
vector<pair<int, int>> wps;

bool check(int d) {
  memset(vis, 0, sizeof(vis));

  queue<pair<int, int>> q;
  q.push(wps[0]);
  vis[wps[0].first][wps[0].second] = true;

  while (!q.empty()) {
    auto cur = q.front();
    auto [ci, cj] = cur;
    q.pop();

    for (int i = 0; i < 4; i++) {
      int ni = ci + dx[i];
      int nj = cj + dy[i];
      if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
      if (abs(board[ni][nj] - board[ci][cj]) <= d && !vis[ni][nj]) {
        vis[ni][nj] = true;
        q.push({ni, nj});
      }
    }
  }

  bool able = true;
  for (auto [i, j] : wps) able &= vis[i][j];
  return able;
}

int main() {
  fast_io();

  cin >> n >> m;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> board[i][j];

  int s;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    cin >> s;
    if (s) wps.push_back({i, j});
  }

  int left = 0, right = 1e9 + 1;
  int mid = (left + right) / 2;
  while (left < right) {
    if (!check(mid)) left = mid + 1;
    else right = mid;

    mid = (left + right) / 2;
  }
  cout << mid << '\n';
}
