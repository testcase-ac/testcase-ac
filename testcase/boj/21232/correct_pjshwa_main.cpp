#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 4000, BIAS = 2000;
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
bool board[MAX + 1][MAX + 1], wait[MAX + 1][MAX + 1], vis[MAX + 1][MAX + 1];
int adj[MAX + 1][MAX + 1];
int total;

void ff(int x, int y);

bool present(int x, int y) {
  return board[x][y] || wait[x][y];
}

void place(int x, int y, bool v) {
  if (v) wait[x][y] = 1;
  else board[x][y] = 1;
  total++;

  if (adj[x][y] == 3) ff(x, y);

  for (int k = 0; k < 4; k++) {
    int nx = x + dx[k], ny = y + dy[k];
    adj[nx][ny]++;
    if (adj[nx][ny] == 3 && present(nx, ny)) ff(nx, ny);
  }
}

// Find empty spot to fill
void ff(int x, int y) {
  for (int k = 0; k < 4; k++) {
    int nx = x + dx[k], ny = y + dy[k];
    if (!present(nx, ny)) {
      place(nx, ny, 1);
      break;
    }
  }
}

void solve() {
  int N;
  cin >> N;

  for (int i = 1; i <= N; i++) {
    int x, y;
    cin >> x >> y;
    x += BIAS, y += BIAS;

    if (wait[x][y] == 1) {
      wait[x][y] = 0;
      board[x][y] = 1;
    }
    else {
      place(x, y, 0);
    }

    cout << total - i << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
