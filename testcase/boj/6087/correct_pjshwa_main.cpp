#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using tii = tuple<int, int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100, INF = 0x3f3f3f3f;
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
char board[MAX + 1][MAX + 1];
int cdist[MAX + 1][MAX + 1][2];
int N, M;

void dijk(int si, int sj) {
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    cdist[i][j][0] = cdist[i][j][1] = INF;
  }

  priority_queue<tii, vector<tii>, greater<tii>> pq;
  for (int l = 0; l < 2; l++) {
    pq.push({0, si, sj, l});
    cdist[si][sj][l] = 0;
  }

  while (!pq.empty()) {
    auto [w, ui, uj, uk] = pq.top();
    pq.pop();

    if (w > cdist[ui][uj][uk]) continue;

    if (cdist[ui][uj][uk ^ 1] > w + 1) {
      cdist[ui][uj][uk ^ 1] = w + 1;
      pq.push({w + 1, ui, uj, uk ^ 1});
    }

    for (int d = 0; d < 2; d++) {
      int k = (2 * d + uk);

      int vi = ui + dx[k], vj = uj + dy[k];
      if (vi < 0 || vi >= N || vj < 0 || vj >= M) continue;
      if (board[vi][vj] == '*') continue;

      if (cdist[vi][vj][uk] > w) {
        cdist[vi][vj][uk] = w;
        pq.push({w, vi, vj, uk});
      }
    }
  }
}

void solve() {
  cin >> M >> N;

  int si = -1, sj, ei, ej;
  for (int i = 0; i < N; i++) {
    cin >> board[i];
    for (int j = 0; j < M; j++) {
      if (board[i][j] == 'C') {
        if (si == -1) si = i, sj = j;
        else ei = i, ej = j;
      }
    }
  }

  dijk(si, sj);
  cout << min(cdist[ei][ej][0], cdist[ei][ej][1]) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
