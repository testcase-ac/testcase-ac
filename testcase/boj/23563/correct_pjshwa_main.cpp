#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 500;
const ll INF = 1e14;
char board[MAX + 1][MAX + 1];
int n, m, si, sj, ei, ej;
ll cdist[MAX][MAX];

bool near_wall(int i, int j) {
  if (i > 0 && board[i - 1][j] == '#') return true;
  if (i < n - 1 && board[i + 1][j] == '#') return true;
  if (j > 0 && board[i][j - 1] == '#') return true;
  if (j < m - 1 && board[i][j + 1] == '#') return true;
  return false;
}

int dist(int ai, int aj, int bi, int bj) {
  if (near_wall(ai, aj) && near_wall(bi, bj)) return 0;
  else return 1;
}

void dijk() {
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cdist[i][j] = INF;
  cdist[si][sj] = 0;

  priority_queue<tuple<ll, int, int>, vector<tuple<ll, int, int>>, greater<tuple<ll, int, int>>> pq;
  pq.push({0, si, sj});

  while (!pq.empty()) {
    auto [wi, ui, uj] = pq.top();
    pq.pop();

    if (wi > cdist[ui][uj]) continue;

    if (ui > 0 && board[ui - 1][uj] == '.' && cdist[ui - 1][uj] > wi + dist(ui - 1, uj, ui, uj)) {
      cdist[ui - 1][uj] = wi + dist(ui - 1, uj, ui, uj);
      pq.push({cdist[ui - 1][uj], ui - 1, uj});
    }
    if (ui < n - 1 && board[ui + 1][uj] == '.' && cdist[ui + 1][uj] > wi + dist(ui + 1, uj, ui, uj)) {
      cdist[ui + 1][uj] = wi + dist(ui + 1, uj, ui, uj);
      pq.push({cdist[ui + 1][uj], ui + 1, uj});
    }
    if (uj > 0 && board[ui][uj - 1] == '.' && cdist[ui][uj - 1] > wi + dist(ui, uj - 1, ui, uj)) {
      cdist[ui][uj - 1] = wi + dist(ui, uj - 1, ui, uj);
      pq.push({cdist[ui][uj - 1], ui, uj - 1});
    }
    if (uj < m - 1 && board[ui][uj + 1] == '.' && cdist[ui][uj + 1] > wi + dist(ui, uj + 1, ui, uj)) {
      cdist[ui][uj + 1] = wi + dist(ui, uj + 1, ui, uj);
      pq.push({cdist[ui][uj + 1], ui, uj + 1});
    }
  }
}

int main() {
  fast_io();

  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> board[i];
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (board[i][j] == 'S') {
      board[i][j] = '.';
      si = i;
      sj = j;
    }
    if (board[i][j] == 'E') {
      board[i][j] = '.';
      ei = i;
      ej = j;
    }
  }

  dijk();
  cout << cdist[ei][ej] << '\n';
}
