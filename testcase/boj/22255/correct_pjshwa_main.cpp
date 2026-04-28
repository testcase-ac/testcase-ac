#include <bits/stdc++.h>
typedef long long ll;
#define pll pair<ll, ll>
using namespace std;

const ll MAX = 1e18;
ll cdist[30003];
vector<pll> graph[30003];
int board[100][100];

void dijk(int s) {
  cdist[s] = 0;

  priority_queue<pll, vector<pll>, greater<pll>> pq;
  pq.push({0, s});

  while (!pq.empty()) {
    auto[wi, ui] = pq.top();
    pq.pop();

    if (wi > cdist[ui]) continue;

    for (auto &p : graph[ui]) {
      auto[vi, di] = p;
      if (cdist[vi] > di + wi) {
        cdist[vi] = di + wi;
        pq.push({cdist[vi], vi});
      }
    }
  }
}

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, m, sx, sy, ex, ey;
  cin >> n >> m >> sx >> sy >> ex >> ey;
  sx--; sy--; ex--; ey--;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> board[i][j];

  int mag = n * m;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (board[i][j] == -1) continue;

    int cx = i * m + j;
    if (i > 0 && board[i - 1][j] >= 0) {
      int nx = (i - 1) * m + j;
      graph[cx].push_back({nx + mag, board[i - 1][j]});
      graph[cx + mag].push_back({nx + 2 * mag, board[i - 1][j]});
    }

    if (i < n - 1 && board[i + 1][j] >= 0) {
      int nx = (i + 1) * m + j;
      graph[cx].push_back({nx + mag, board[i + 1][j]});
      graph[cx + mag].push_back({nx + 2 * mag, board[i + 1][j]});
    }

    if (j > 0 && board[i][j - 1] >= 0) {
      int nx = i * m + j - 1;
      graph[cx].push_back({nx + mag, board[i][j - 1]});
      graph[cx + 2 * mag].push_back({nx, board[i][j - 1]});
    }

    if (j < m - 1 && board[i][j + 1] >= 0) {
      int nx = i * m + j + 1;
      graph[cx].push_back({nx + mag, board[i][j + 1]});
      graph[cx + 2 * mag].push_back({nx, board[i][j + 1]});
    }

  }

  fill(cdist, cdist + 30003, MAX);
  dijk(sx * m + sy + mag);

  ll mv = min({cdist[ex * m + ey], cdist[ex * m + ey + mag], cdist[ex * m + ey + 2 * mag]});
  cout << (mv == MAX ? -1 : mv) << '\n';
}
