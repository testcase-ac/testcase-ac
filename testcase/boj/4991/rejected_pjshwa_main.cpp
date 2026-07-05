#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 20, INF = 1e9 + 7;
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};
char board[MAX + 1][MAX + 1];
int cdist[11][MAX][MAX];
bool vis[MAX][MAX];
int n, m;

void bfs(int d, int si, int sj) {
  memset(vis, 0, sizeof(vis));
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cdist[d][i][j] = INF;

  queue<tii> q;
  q.push({si, sj, 0});
  vis[si][sj] = true;

  while (!q.empty()) {
    auto [ci, cj, cc] = q.front();
    q.pop();

    cdist[d][ci][cj] = cc;

    for (int k = 0; k < 4; ++k) {
      int ni = ci + dx[k], nj = cj + dy[k];
      if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
      if (vis[ni][nj]) continue;
      if (board[ni][nj] == 'x') continue;
      q.push({ni, nj, cc + 1});
      vis[ni][nj] = true;
    }
  }
}

void solve() {
  for (int i = 0; i < n; i++) cin >> board[i];

  vector<pii> ims;
  int si, sj;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (board[i][j] == 'o') si = i, sj = j;
    if (board[i][j] == '*') ims.push_back({i, j});
  }

  bfs(0, si, sj);
  int sz = ims.size();
  for (int i = 0; i < sz; i++) bfs(i + 1, ims[i].first, ims[i].second);

  ll ans = INF;
  int p[10];
  for (int i = 0; i < sz; i++) p[i] = i;
  do {
    ll cur = cdist[0][ims[p[0]].first][ims[p[0]].second];
    for (int i = 0; i < sz - 1; i++) {
      cur += cdist[p[i] + 1][ims[p[i + 1]].first][ims[p[i + 1]].second];
    }
    ans = min(ans, cur);
  } while (next_permutation(p, p + sz));

  if (ans == INF) cout << "-1\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  while (1) {
    cin >> m >> n;
    if (n == 0 && m == 0) break;
    solve();
  }
}
