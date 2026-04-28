#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using tiii = tuple<int, int, int, int>;
using ld = long double;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100, INF = 1e9 + 7;
char board[MAX + 1][MAX + 1];

// N, E, S, W
int cdist[4][MAX][MAX];
int n;
int si, sj, ei, ej;

void dijk() {
  for (int d = 0; d < 4; d++) {
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cdist[d][i][j] = INF;
    cdist[d][si][sj] = 0;
  }

  priority_queue<tiii, vector<tiii>, greater<tiii>> pq;
  for (int dir = 0; dir < 4; dir++) pq.push({0, dir, si, sj});

  while (!pq.empty()) {
    auto [wi, cd, ui, uj] = pq.top();
    pq.pop();

    if (wi > cdist[cd][ui][uj]) continue;

    for (int d = 0; d < 4; d++) {
      if (cd != d && cdist[d][ui][uj] > wi + 1) {
        cdist[d][ui][uj] = wi + 1;
        pq.push({cdist[d][ui][uj], d, ui, uj});
      }
    }

    if (cd == 0 && ui > 0 && board[ui - 1][uj] != 'x' && cdist[cd][ui - 1][uj] > wi) {
      cdist[cd][ui - 1][uj] = wi;
      pq.push({cdist[cd][ui - 1][uj], cd, ui - 1, uj});
    }
    if (cd == 1 && uj < n - 1 && board[ui][uj + 1] != 'x' && cdist[cd][ui][uj + 1] > wi) {
      cdist[cd][ui][uj + 1] = wi;
      pq.push({cdist[cd][ui][uj + 1], cd, ui, uj + 1});
    }
    if (cd == 2 && ui < n - 1 && board[ui + 1][uj] != 'x' && cdist[cd][ui + 1][uj] > wi) {
      cdist[cd][ui + 1][uj] = wi;
      pq.push({cdist[cd][ui + 1][uj], cd, ui + 1, uj});
    }
    if (cd == 3 && uj > 0 && board[ui][uj - 1] != 'x' && cdist[cd][ui][uj - 1] > wi) {
      cdist[cd][ui][uj - 1] = wi;
      pq.push({cdist[cd][ui][uj - 1], cd, ui, uj - 1});
    }
  }
}

int main() {
  fast_io();

  cin >> n;
  for (int i = 0; i < n; i++) cin >> board[i];
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    if (board[i][j] == 'A') si = i, sj = j;
    if (board[i][j] == 'B') ei = i, ej = j;
  }

  dijk();

  int ans = INF;
  for (int dir = 0; dir < 4; dir++) ans = min(ans, cdist[dir][ei][ej]);
  cout << ans << '\n';
}
