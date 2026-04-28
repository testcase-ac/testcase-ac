#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 7;
const int dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0};
int N, M, A[MAXN][MAXN], cdist[MAXN][MAXN][MAXN][MAXN];

void solve() {
  int si, sj, bi, bj, ei, ej;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    cin >> A[i][j];
    if (A[i][j] == 2) bi = i, bj = j;
    if (A[i][j] == 3) ei = i, ej = j;
    if (A[i][j] == 4) si = i, sj = j;
  }

  memset(cdist, -1, sizeof(cdist));
  deque<tuple<int, int, int, int>> Q;
  Q.emplace_back(si, sj, bi, bj); cdist[si][sj][bi][bj] = 0;
  auto oob = [&](int i, int j) {
    return i < 0 || i >= N || j < 0 || j >= M || A[i][j] == 1;
  };

  while (!Q.empty()) {
    auto [ci, cj, cbi, cbj] = Q.front(); Q.pop_front();
    int d = cdist[ci][cj][cbi][cbj];
    if (cbi == ei && cbj == ej) return cout << d << '\n', void();

    for (int k = 0; k < 4; ++k) {
      int nci = ci + dx[k], ncj = cj + dy[k];
      if (oob(nci, ncj) || (nci == cbi && ncj == cbj) || cdist[nci][ncj][cbi][cbj] != -1) continue;
      cdist[nci][ncj][cbi][cbj] = d;
      Q.emplace_front(nci, ncj, cbi, cbj);
    }

    // player can push the box
    if (abs(ci - cbi) + abs(cj - cbj) == 1) {
      int nbi = cbi + (cbi - ci), nbj = cbj + (cbj - cj);
      if (oob(nbi, nbj) || cdist[cbi][cbj][nbi][nbj] != -1) continue;
      cdist[cbi][cbj][nbi][nbj] = d + 1;
      Q.emplace_back(cbi, cbj, nbi, nbj);
    }
  }

  cout << "-1\n";
}

int main() {
  fast_io();

  while (cin >> M >> N) {
    if (N == 0 && M == 0) break;
    solve();
  }
}
