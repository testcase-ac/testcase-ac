#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 200;
char texture[MAXN + 1][MAXN + 1];
char board[MAXN + 1][MAXN + 1];

void solve() {
  int N, M, U, V; cin >> N >> M >> U >> V;
  for (int i = 0; i < U; ++i) cin >> texture[i];

  string op; cin >> op;
  if (op == "clamp-to-edge") {
    for (int i = 0; i < MAXN; ++i) for (int j = 0; j < MAXN; ++j) {
      if (i < U) {
        if (j < V) board[i][j] = texture[i][j];
        else board[i][j] = texture[i][V - 1];
      } else {
        if (j < V) board[i][j] = texture[U - 1][j];
        else board[i][j] = texture[U - 1][V - 1];
      }
    }
  } else if (op == "repeat") {
    for (int i = 0; i < MAXN; ++i) for (int j = 0; j < MAXN; ++j) {
      board[i][j] = texture[i % U][j % V];
    }
  } else if (op == "mirrored-repeat") {
    for (int i = 0; i < MAXN; ++i) for (int j = 0; j < MAXN; ++j) {
      if ((i / U) % 2 == 0) {
        if ((j / V) % 2 == 0) board[i][j] = texture[i % U][j % V];
        else board[i][j] = texture[i % U][V - 1 - j % V];
      } else {
        if ((j / V) % 2 == 0) board[i][j] = texture[U - 1 - i % U][j % V];
        else board[i][j] = texture[U - 1 - i % U][V - 1 - j % V];
      }
    }
  }

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) cout << board[i][j];
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
