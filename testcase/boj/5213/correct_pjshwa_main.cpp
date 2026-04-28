#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000, INF = 1e9 + 7;
int board[MAX + 1][MAX + 1], tnum[MAX + 1][MAX + 1];
vector<int> graph[MAX * MAX + 1];
int from[MAX * MAX + 1], cdist[MAX * MAX + 1];

void solve() {
  int n;
  cin >> n;

  memset(board, -1, sizeof(board));

  int tile = 0;
  for (int i = 1; i <= n; i++) {
    if (i & 1) {
      for (int j = 1; j <= 2 * n; j++) {
        cin >> board[i][j];
        tnum[i][j] = (++tile + 1) / 2;
      }
    }
    else {
      for (int j = 2; j <= 2 * n - 1; j++) {
        cin >> board[i][j];
        tnum[i][j] = (++tile + 1) / 2;
      }
    }
  }

  for (int i = 1; i <= n; i++) for (int j = 1; j <= 2 * n; j++) {
    if (board[i][j] == -1) continue;
    if (i > 1) {
      if (board[i][j] == board[i - 1][j]) {
        graph[tnum[i][j]].push_back(tnum[i - 1][j]);
        graph[tnum[i - 1][j]].push_back(tnum[i][j]);
      }
    }
    if (j > 1) {
      if (board[i][j] == board[i][j - 1] && tnum[i][j] != tnum[i][j - 1]) {
        graph[tnum[i][j]].push_back(tnum[i][j - 1]);
        graph[tnum[i][j - 1]].push_back(tnum[i][j]);
      }
    }
  }

  queue<int> q;
  q.push(1);

  fill(cdist, cdist + MAX * MAX + 1, INF);
  memset(from, -1, sizeof(from));
  cdist[1] = 0;

  while (!q.empty()) {
    int v = q.front();
    q.pop();

    for (int u : graph[v]) {
      if (cdist[u] > cdist[v] + 1) {
        cdist[u] = cdist[v] + 1;
        from[u] = v;
        q.push(u);
      }
    }
  }

  for (int mtile = (tile + 1) / 2; mtile >= 1; mtile--) {
    if (cdist[mtile] == INF) continue;

    int e = mtile;
    stack<int> traj;
    while (e != -1) {
      traj.push(e);
      e = from[e];
    }

    cout << traj.size() << '\n';
    while (!traj.empty()) {
      cout << traj.top() << ' ';
      traj.pop();
    }
    cout << '\n';

    break;
  }
  
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
