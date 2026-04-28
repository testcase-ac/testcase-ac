#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1 << 16, INF = 0x3f3f3f3f;
int cdist[MAX];

void solve() {
  int N; cin >> N;

  set<int> masks;
  for (int i = 0; i < N; i++) {
    int x, y; cin >> x >> y;

    for (int i = -3; i <= 3; i++) for (int j = -3; j <= 3; j++) {
      bool M[4][4]{};
      for (int k = 0; k < x; k++) for (int l = 0; l < y; l++) {
        int ni = i + k, nj = j + l;
        if (ni < 0 || ni >= 4 || nj < 0 || nj >= 4) continue;
        M[ni][nj] = 1;
      }

      int mask = 0;
      for (int k = 0; k < 4; k++) for (int l = 0; l < 4; l++) {
        if (M[k][l]) mask |= (1 << (k * 4 + l));
      }
      masks.insert(mask);
    }
  }

  char board[5][5];
  for (int i = 0; i < 4; i++) cin >> board[i];

  fill(cdist, cdist + MAX, INF);
  queue<int> q;
  q.push(0), cdist[0] = 0;

  int dest = MAX - 1;

  while (!q.empty()) {
    auto v = q.front(); q.pop();

    if (v == dest) {
      cout << cdist[v] << '\n';
      return;
    }

    bool B[4][4];
    for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) {
      B[i][j] = (v & (1 << (i * 4 + j))) ? 1 : 0;
    }

    for (int mask : masks) {
      for (char c : {'R', 'G', 'B'}) {
        bool NB[4][4];
        for (int k = 0; k < 4; k++) for (int l = 0; l < 4; l++) NB[k][l] = B[k][l];
        for (int k = 0; k < 4; k++) for (int l = 0; l < 4; l++) {
          if (!(mask & (1 << (k * 4 + l)))) continue;
          NB[k][l] = (c == board[k][l]);
        }

        int nstate = 0;
        for (int k = 0; k < 4; k++) for (int l = 0; l < 4; l++) {
          nstate |= (NB[k][l] << (k * 4 + l));
        }

        if (cdist[nstate] == INF) {
          cdist[nstate] = cdist[v] + 1;
          q.push(nstate);
        }
      }
    }

  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
