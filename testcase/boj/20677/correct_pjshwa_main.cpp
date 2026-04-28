#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 500, INF = 0x3f3f3f3f;
const int dx[8] = {1, 0, -1, 0, 1, 1, -1, -1};
const int dy[8] = {0, 1, 0, -1, 1, -1, 1, -1};
char board[MAXN + 1][MAXN + 1];
int D[MAXN][MAXN], parent[MAXN * MAXN];

int Find(int x) {
  if (parent[x] == x) return x;
  return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
  x = Find(x), y = Find(y);
  if (x != y) parent[x] = y;
}

void solve() {
  int N, M; cin >> N >> M;

  int si, sj, ei, ej, pcnt = 0;
  memset(D, 0x3f, sizeof(D));

  queue<pii> Q;
  for (int i = 0; i < N; ++i) {
    cin >> board[i];
    for (int j = 0; j < M; ++j) {
      if (board[i][j] == 'S') si = i, sj = j;
      if (board[i][j] == 'E') ei = i, ej = j;
      if (board[i][j] == '*') {
        ++pcnt;
        Q.emplace(i, j); D[i][j] = 0;
      }
    }
  }

  while (!Q.empty()) {
    auto [i, j] = Q.front(); Q.pop();
    for (int k = 0; k < 8; ++k) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;
      if (D[ni][nj] > D[i][j] + 1) {
        D[ni][nj] = D[i][j] + 1;
        Q.emplace(ni, nj);
      }
    }
  }

  vector<tuple<int, int, int>> V; vector<int> O;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    if (board[i][j] == '#' || board[i][j] == '*') continue;
    V.emplace_back(D[i][j], i, j);
    O.push_back(D[i][j]);
  }
  sort(V.begin(), V.end(), greater<>());
  sort(O.begin(), O.end(), greater<>());
  O.erase(unique(O.begin(), O.end()), O.end());

  iota(parent, parent + N * M, 0); int i = 0, S = si * M + sj, E = ei * M + ej;
  for (int o : O) {
    while (i < V.size() && get<0>(V[i]) == o) {
      auto [d, x, y] = V[i];
      for (int k = 0; k < 4; ++k) {
        int nx = x + dx[k], ny = y + dy[k];
        if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
        if (board[nx][ny] == '#' || board[nx][ny] == '*') continue;
        if (D[nx][ny] >= D[x][y]) Union(x * M + y, nx * M + ny);
      }
      ++i;
    }
    if (Find(S) == Find(E)) {
      if (o == INF) cout << "safe\n";
      else cout << o << '\n';
      return;
    }
  }

  cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
