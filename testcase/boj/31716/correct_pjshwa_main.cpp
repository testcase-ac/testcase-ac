#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 0x3f3f3f3f;
const int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};

void solve() {
  int M, K; cin >> M >> K;
  string S[2]; cin >> S[0] >> S[1];

  int D[2][2]; memset(D, 0x3f, sizeof(D));
  for (int i = 0; i < 2; ++i) {
    vector<vector<int>> cdist(2, vector<int>(M, INF));
    if (S[i][0] == '#') continue;

    cdist[i][0] = 0; queue<pii> Q; Q.emplace(i, 0);
    while (!Q.empty()) {
      auto [x, y] = Q.front(); Q.pop();
      for (int j = 0; j < 4; ++j) {
        int nx = x + dx[j], ny = y + dy[j];
        if (nx < 0 || nx >= 2 || ny < 0 || ny >= M) continue;
        if (S[nx][ny] != '#' && cdist[nx][ny] > cdist[x][y] + 1) {
          cdist[nx][ny] = cdist[x][y] + 1;
          Q.emplace(nx, ny);
        }
      }
    }

    for (int j = 0; j < 2; ++j) D[i][j] = cdist[j][M - 1];
  }

  int H[2][2]; memset(H, 0x3f, sizeof(H));
  for (int s = 0; s < 2; ++s) for (int i = 0; i < 2; ++i) {
    if (S[i][0] == '#') continue;

    H[s][i] = min(H[s][i], D[s][i] + 1);
    if (S[1 - i][0] != '#') H[s][i] = min(H[s][i], D[s][1 - i] + 2);
  }

  ll ans = 1e18;
  for (int i = 0; i < 2; ++i) {
    if (K > 1 && H[i][i] == INF) continue;
    ll val = (ll)(K - 1) * H[i][i];
    ans = min(ans, val + min(D[i][0], D[i][1]));
  }
  if (ans == 1e18) cout << "-1\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
