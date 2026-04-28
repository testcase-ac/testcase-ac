#include <bits/stdc++.h>
using namespace std;
using tiii = tuple<int, int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50;
char board[MAX + 1][MAX + 1];
int vis[64][MAX][MAX];

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> board[i];

  int si, sj;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (board[i][j] == '0') {
      board[i][j] = '.';
      si = i;
      sj = j;
    }
  }

  queue<tiii> q;
  q.push({0, si, sj, 0});
  vis[0][si][sj] = 1;

  while (!q.empty()) {
    auto [dim, i, j, dist] = q.front();
    q.pop();

    if (board[i][j] == '1') {
      cout << dist << '\n';
      return 0;
    }

    if (i > 0) {
      if ((board[i - 1][j] == '.' || board[i - 1][j] == '1') && !vis[dim][i - 1][j]) {
        vis[dim][i - 1][j] = 1;
        q.push({dim, i - 1, j, dist + 1});
      }
      if ('a' <= board[i - 1][j] && board[i - 1][j] <= 'f') {
        int nkey = board[i - 1][j] - 'a', ndim = dim | (1 << nkey);
        if (!vis[ndim][i - 1][j]) {
          vis[ndim][i - 1][j] = 1;
          q.push({ndim, i - 1, j, dist + 1});
        }
      }
      if ('A' <= board[i - 1][j] && board[i - 1][j] <= 'F') {
        int nkey = board[i - 1][j] - 'A';
        if ((dim & (1 << nkey)) && !vis[dim][i - 1][j]) {
          q.push({dim, i - 1, j, dist + 1});
          vis[dim][i - 1][j] = 1;
        }
      }
    }

    if (i < n - 1) {
      if ((board[i + 1][j] == '.' || board[i + 1][j] == '1') && !vis[dim][i + 1][j]) {
        vis[dim][i + 1][j] = 1;
        q.push({dim, i + 1, j, dist + 1});
      }
      if ('a' <= board[i + 1][j] && board[i + 1][j] <= 'f') {
        int nkey = board[i + 1][j] - 'a', ndim = dim | (1 << nkey);
        if (!vis[ndim][i + 1][j]) {
          vis[ndim][i + 1][j] = 1;
          q.push({ndim, i + 1, j, dist + 1});
        }
      }
      if ('A' <= board[i + 1][j] && board[i + 1][j] <= 'F') {
        int nkey = board[i + 1][j] - 'A';
        if ((dim & (1 << nkey)) && !vis[dim][i + 1][j]) {
          q.push({dim, i + 1, j, dist + 1});
          vis[dim][i + 1][j] = 1;
        }
      }
    }

    if (j > 0) {
      if ((board[i][j - 1] == '.' || board[i][j - 1] == '1') && !vis[dim][i][j - 1]) {
        vis[dim][i][j - 1] = 1;
        q.push({dim, i, j - 1, dist + 1});
      }
      if ('a' <= board[i][j - 1] && board[i][j - 1] <= 'f') {
        int nkey = board[i][j - 1] - 'a', ndim = dim | (1 << nkey);
        if (!vis[ndim][i][j - 1]) {
          vis[ndim][i][j - 1] = 1;
          q.push({ndim, i, j - 1, dist + 1});
        }
      }
      if ('A' <= board[i][j - 1] && board[i][j - 1] <= 'F') {
        int nkey = board[i][j - 1] - 'A';
        if ((dim & (1 << nkey)) && !vis[dim][i][j - 1]) {
          q.push({dim, i, j - 1, dist + 1});
          vis[dim][i][j - 1] = 1;
        }
      }
    }

    if (j < m - 1) {
      if ((board[i][j + 1] == '.' || board[i][j + 1] == '1') && !vis[dim][i][j + 1]) {
        vis[dim][i][j + 1] = 1;
        q.push({dim, i, j + 1, dist + 1});
      }
      if ('a' <= board[i][j + 1] && board[i][j + 1] <= 'f') {
        int nkey = board[i][j + 1] - 'a', ndim = dim | (1 << nkey);
        if (!vis[ndim][i][j + 1]) {
          vis[ndim][i][j + 1] = 1;
          q.push({ndim, i, j + 1, dist + 1});
        }
      }
      if ('A' <= board[i][j + 1] && board[i][j + 1] <= 'F') {
        int nkey = board[i][j + 1] - 'A';
        if ((dim & (1 << nkey)) && !vis[dim][i][j + 1]) {
          q.push({dim, i, j + 1, dist + 1});
          vis[dim][i][j + 1] = 1;
        }
      }
    }
  }

  cout << "-1\n";
}
