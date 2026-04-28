#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXM = 2e5, INFD = 0x3f3f3f3f, INFV = 1e18;
const int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
int O[MAXM], D[MAXM][2][2];
string S[MAXM][2];

void solve() {
  int M, K; cin >> M >> K;
  for (int k = 0; k < K; ++k) cin >> O[k], --O[k];

  memset(D, 0x3f, sizeof(D));
  queue<pii> Q;
  for (int m = 0; m < M; ++m) {
    cin >> S[m][0] >> S[m][1];
    int Z = S[m][0].size();

    for (int i = 0; i < 2; ++i) {
      vector<vector<int>> cdist(2, vector<int>(Z, INFD));
      if (S[m][i][0] == '#') continue;

      cdist[i][0] = 0; Q.emplace(i, 0);
      while (!Q.empty()) {
        auto [x, y] = Q.front(); Q.pop();
        for (int j = 0; j < 4; ++j) {
          int nx = x + dx[j], ny = y + dy[j];
          if (nx < 0 || nx >= 2 || ny < 0 || ny >= Z) continue;
          if (S[m][nx][ny] != '#' && cdist[nx][ny] > cdist[x][y] + 1) {
            cdist[nx][ny] = cdist[x][y] + 1;
            Q.emplace(nx, ny);
          }
        }
      }

      for (int j = 0; j < 2; ++j) D[m][i][j] = cdist[j][Z - 1];
    }
  }

  ll p0 = 0, p1 = 0;
  for (int k = 0; k < K; ++k) {
    ll e0 = INFV, e1 = INFV;
    if (D[O[k]][0][0] != INFD) e0 = min(e0, p0 + D[O[k]][0][0]);
    if (D[O[k]][1][0] != INFD) e0 = min(e0, p1 + D[O[k]][1][0]);
    if (D[O[k]][0][1] != INFD) e1 = min(e1, p0 + D[O[k]][0][1]);
    if (D[O[k]][1][1] != INFD) e1 = min(e1, p1 + D[O[k]][1][1]);

    if (k == K - 1) {
      ll ans = min(e0, e1);
      if (ans == INFV) cout << "-1\n";
      else cout << ans << '\n';
    }
    else {
      // Just do a small bfs here...
      char B[2][2];
      B[0][0] = S[O[k]][0].back(); B[0][1] = S[O[k]][1].back();
      B[1][0] = S[O[k + 1]][0].front(); B[1][1] = S[O[k + 1]][1].front();

      ll cdist[2][2];
      if (B[0][0] != '#') Q.emplace(0, 0), cdist[0][0] = e0;
      if (B[0][1] != '#') Q.emplace(0, 1), cdist[0][1] = e1;
      fill(cdist[1], cdist[1] + 2, INFV);

      while (!Q.empty()) {
        auto [x, y] = Q.front(); Q.pop();
        for (int j = 0; j < 4; ++j) {
          int nx = x + dx[j], ny = y + dy[j];
          if (nx < 0 || nx >= 2 || ny < 0 || ny >= 2) continue;
          if (B[nx][ny] != '#' && cdist[nx][ny] > cdist[x][y] + 1) {
            cdist[nx][ny] = cdist[x][y] + 1;
            Q.emplace(nx, ny);
          }
        }
      }

      p0 = cdist[1][0], p1 = cdist[1][1];
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
