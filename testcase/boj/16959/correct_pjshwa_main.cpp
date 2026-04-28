#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 10;
const int dx_k[] = {-2, -2, -1, -1, 1, 1, 2, 2}, dy_k[] = {-1, 1, -2, 2, -2, 2, -1, 1};
const int dx_b[] = {-1, -1, 1, 1}, dy_b[] = {-1, 1, -1, 1};
const int dx_r[] = {-1, 0, 1, 0}, dy_r[] = {0, 1, 0, -1};

int B[MAXN][MAXN];
int X[MAXN * MAXN + 1], Y[MAXN * MAXN + 1];
int cdist[MAXN][MAXN][3];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
    cin >> B[i][j];
    X[B[i][j]] = i; Y[B[i][j]] = j;
  }

  int U[3]{};
  for (int s = 1; s < N * N; ++s) {
    memset(cdist, 0x3f, sizeof(cdist));

    queue<tuple<int, int, int>> q;
    for (int t = 0; t < 3; ++t) {
      cdist[X[s]][Y[s]][t] = U[t];
      q.emplace(X[s], Y[s], t);
    }

    while (!q.empty()) {
      auto [i, j, t] = q.front(); q.pop();

      // Knight
      if (t == 0) {
        for (int k = 0; k < 8; ++k) {
          int ni = i + dx_k[k], nj = j + dy_k[k];
          if (ni < 0 || ni >= N || nj < 0 || nj >= N) continue;
          if (cdist[ni][nj][t] > cdist[i][j][t] + 1) {
            cdist[ni][nj][t] = cdist[i][j][t] + 1;
            q.emplace(ni, nj, t);
          }
        }
      }
      // Bishop
      if (t == 1) {
        for (int k = 0; k < 4; ++k) {
          for (int l = 1; l < N; ++l) {
            int ni = i + dx_b[k] * l, nj = j + dy_b[k] * l;
            if (ni < 0 || ni >= N || nj < 0 || nj >= N) break;
            if (cdist[ni][nj][t] > cdist[i][j][t] + 1) {
              cdist[ni][nj][t] = cdist[i][j][t] + 1;
              q.emplace(ni, nj, t);
            }
          }
        }
      }
      // Rook
      if (t == 2) {
        for (int k = 0; k < 4; ++k) {
          for (int l = 1; l < N; ++l) {
            int ni = i + dx_r[k] * l, nj = j + dy_r[k] * l;
            if (ni < 0 || ni >= N || nj < 0 || nj >= N) break;
            if (cdist[ni][nj][t] > cdist[i][j][t] + 1) {
              cdist[ni][nj][t] = cdist[i][j][t] + 1;
              q.emplace(ni, nj, t);
            }
          }
        }
      }

      // Switch
      for (int nt = 0; nt < 3; ++nt) {
        if (nt == t) continue;
        if (cdist[i][j][nt] > cdist[i][j][t] + 1) {
          cdist[i][j][nt] = cdist[i][j][t] + 1;
          q.emplace(i, j, nt);
        }
      }
    }

    for (int t = 0; t < 3; ++t) {
      U[t] = cdist[X[s + 1]][Y[s + 1]][t];
    }
  }

  cout << *min_element(U, U + 3) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
