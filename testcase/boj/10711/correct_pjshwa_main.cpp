#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
const int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1}, dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int B[MAXN][MAXN], P[MAXN][MAXN];

void solve() {
  int H, W; cin >> H >> W;
  for (int i = 0; i < H; ++i) {
    string S; cin >> S;
    for (int j = 0; j < W; ++j) {
      if (S[j] == '.') continue;
      B[i][j] = 1;
      P[i][j] = S[j] - '0';
    }
  }

  for (int i = 0; i < H; ++i) for (int j = 0; j < W; ++j) {
    if (B[i][j] == 0) continue;

    for (int k = 0; k < 8; ++k) {
      int ni = i + dy[k], nj = j + dx[k];
      if (ni < 0 || ni >= H || nj < 0 || nj >= W) continue;
      if (B[ni][nj] == 0) --P[i][j];
    }
  }

  queue<pii> q;
  for (int i = 0; i < H; ++i) for (int j = 0; j < W; ++j) {
    if (B[i][j] == 0) continue;
    if (P[i][j] <= 0) {
      q.push({i, j});
      B[i][j] = 0;
    }
  }

  int ans = 0;
  while (1) {
    ++ans;
    queue<pii> nq;

    while (!q.empty()) {
      auto [i, j] = q.front(); q.pop();

      for (int k = 0; k < 8; ++k) {
        int ni = i + dy[k], nj = j + dx[k];
        if (ni < 0 || ni >= H || nj < 0 || nj >= W) continue;
        if (B[ni][nj] == 0) continue;

        --P[ni][nj];
        if (P[ni][nj] <= 0) {
          nq.push({ni, nj});
          B[ni][nj] = 0;
        }
      }
    }

    if (nq.empty()) break;
    q = nq;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
