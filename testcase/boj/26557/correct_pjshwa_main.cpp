#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 0x3f3f3f3f;
const int dx[6] = {0, 0, 1, -1, 0, 0}, dy[6] = {1, -1, 0, 0, 0, 0}, dz[6] = {0, 0, 0, 0, 1, -1};

void solve() {
  int f, r, c;
  cin >> f >> r >> c;

  vector<vector<string>> B(f, vector<string>(r));
  int sf, sr, sc, ef, er, ec;
  for (int i = 0; i < f; i++) {
    for (int j = 0; j < r; j++) {
      cin >> B[i][j];
      for (int k = 0; k < c; k++) {
        if (B[i][j][k] == 'S') sf = i, sr = j, sc = k;
        if (B[i][j][k] == 'E') ef = i, er = j, ec = k;
      }
    }
  }

  vector<vector<vector<int>>> D(f, vector<vector<int>>(r, vector<int>(c, INF)));
  deque<tii> Q;
  Q.emplace_back(sf, sr, sc);
  D[sf][sr][sc] = 0;

  while (!Q.empty()) {
    auto [cf, cr, cc] = Q.front(); Q.pop_front();

    for (int k = 0; k < 6; k++) {
      int nf = cf + dz[k], nr = cr + dy[k], nc = cc + dx[k];
      if (nf < 0 || nf >= f || nr < 0 || nr >= r || nc < 0 || nc >= c) continue;

      if (B[nf][nr][nc] == '#') {
        if (D[nf][nr][nc] > D[cf][cr][cc] + 1) {
          D[nf][nr][nc] = D[cf][cr][cc] + 1;
          Q.emplace_back(nf, nr, nc);
        }
      }
      else {
        if (D[nf][nr][nc] > D[cf][cr][cc]) {
          D[nf][nr][nc] = D[cf][cr][cc];
          Q.emplace_front(nf, nr, nc);
        }
      }
    }
  }

  cout << D[ef][er][ec] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
