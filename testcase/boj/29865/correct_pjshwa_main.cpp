#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 8;
const int dx[8] = {1, 1, 2, 2, -1, -1, -2, -2};
const int dy[8] = {2, -2, 1, -1, 2, -2, 1, -1};
int cdist[MAXN][MAXN];

void solve() {
  string S; cin >> S;
  int N = MAXN;

  memset(cdist, -1, sizeof(cdist));
  queue<pii> Q; int r = S[0] - 'a', c = S[1] - '1';
  Q.emplace(r, c); cdist[r][c] = 0;

  while (!Q.empty()) {
    auto [r, c] = Q.front(); Q.pop();
    for (int k = 0; k < 8; ++k) {
      int nr = r + dx[k], nc = c + dy[k];
      if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
      if (cdist[nr][nc] != -1) continue;
      cdist[nr][nc] = cdist[r][c] + 1;
      Q.emplace(nr, nc);
    }
  }

  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
    int dis = cdist[i][j];
    if (dis == 0 || dis == 2) cout << (char)('a' + i) << (char)('1' + j) << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
