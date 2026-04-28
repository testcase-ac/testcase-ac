#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 50;
const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};
vector<int> adj[MAXN * MAXN];
int ma[MAXN * MAXN], mb[MAXN * MAXN], cdist[MAXN][MAXN];
char board[MAXN + 1][MAXN + 1];
bool vis[MAXN * MAXN];

bool dfs(int a) {
  vis[a] = true;
  for (int b : adj[a]) {
    if (mb[b] == -1 || (!vis[mb[b]] && dfs(mb[b]))) {
      ma[a] = b; mb[b] = a;
      return true;
    }
  }
  return false;
}

void solve() {
  int N, M; cin >> N >> M;

  vector<pii> Cs, Ps;
  for (int i = 0; i < N; ++i) {
    cin >> board[i];
    for (int j = 0; j < M; ++j) {
      if (board[i][j] == 'C') Cs.emplace_back(i, j);
      if (board[i][j] == 'P') Ps.emplace_back(i, j);
    }
  }

  int Z1 = Cs.size(), Z2 = Ps.size();
  vector<vector<int>> Ds(Z1, vector<int>(Z2, -1));
  queue<pii> Q;
  for (int i = 0; i < Z1; ++i) {
    auto [si, sj] = Cs[i];
    memset(cdist, -1, sizeof cdist);
    Q.push({si, sj}); cdist[si][sj] = 0;

    while (!Q.empty()) {
      auto [x, y] = Q.front(); Q.pop();
      for (int d = 0; d < 4; ++d) {
        int nx = x + dx[d], ny = y + dy[d];
        if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
        if (cdist[nx][ny] != -1 || board[nx][ny] == 'X') continue;
        cdist[nx][ny] = cdist[x][y] + 1;
        Q.push({nx, ny});
      }
    }

    for (int j = 0; j < Z2; ++j) {
      auto [ti, tj] = Ps[j];
      Ds[i][j] = cdist[ti][tj];
    }
  }

  int l = 0, r = N * M + 1;
  while (l < r) {
    int m = (l + r) / 2;
    for (int i = 0; i < Z1; ++i) {
      adj[i].clear();
      for (int j = 0; j < Z2; ++j) {
        int dist = Ds[i][j];
        if (dist != -1 && dist <= m) adj[i].push_back(j);
      }
    }

    int match = 0;
    memset(ma, -1, sizeof ma);
    memset(mb, -1, sizeof mb);

    for (int i = 0; i < Z1; ++i) {
      if (ma[i] != -1) continue;
      fill(vis, vis + Z1, false);
      if (dfs(i)) ++match;
    }

    if (match == Z1) r = m;
    else l = m + 1;
  }

  if (l == N * M + 1) l = -1;
  cout << l << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
