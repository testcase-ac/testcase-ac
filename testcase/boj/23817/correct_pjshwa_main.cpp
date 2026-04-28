#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000, INF = 1e9 + 7;
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};
char board[MAX + 1][MAX + 1];
int cdist[21][MAX][MAX];
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
      if (board[ni][nj] == 'X') continue;
      q.push({ni, nj, cc + 1});
      vis[ni][nj] = true;
    }
  }
}

void solve() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> board[i];

  vector<pii> stores;
  int si, sj;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (board[i][j] == 'S') si = i, sj = j;
    if (board[i][j] == 'K') stores.push_back({i, j});
  }

  bfs(0, si, sj);
  int sz = stores.size();
  for (int i = 0; i < sz; i++) bfs(i + 1, stores[i].first, stores[i].second);

  ll ans = INF;
  for (int i1 = 0; i1 < sz; i1++) for (int i2 = 0; i2 < sz; i2++) for (int i3 = 0; i3 < sz; i3++)
  for (int i4 = 0; i4 < sz; i4++) for (int i5 = 0; i5 < sz; i5++) {
    if (i1 == i2 || i1 == i3 || i1 == i4 || i1 == i5 ||
        i2 == i3 || i2 == i4 || i2 == i5 ||
        i3 == i4 || i3 == i5 ||
        i4 == i5) continue;

    ll cur = 0;
    cur += cdist[0][stores[i1].first][stores[i1].second];
    cur += cdist[i1 + 1][stores[i2].first][stores[i2].second];
    cur += cdist[i2 + 1][stores[i3].first][stores[i3].second];
    cur += cdist[i3 + 1][stores[i4].first][stores[i4].second];
    cur += cdist[i4 + 1][stores[i5].first][stores[i5].second];
    ans = min(ans, cur);
  }
  
  if (ans == INF) cout << "-1\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
