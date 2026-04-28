#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 60;
char board[MAX + 1][MAX + 1];

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> board[i];

  int S = 0;
  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
    int v = i * N + j;
    S += (1 << v) * (board[i][j] == 'X');
  }

  int E = 0;
  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
    int v = i * N + j;
    E += (1 << v) * (i == j || i + j == N - 1);
  }

  queue<int> q;
  set<int> vis;
  q.push(S); vis.insert(S);

  while (!q.empty()) {
    int v = q.front(); q.pop();

    char board[N + 1][N + 1]{};
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
      int u = i * N + j;
      board[i][j] = (v & (1 << u)) ? 'X' : '.';
    }
    
    // cout << "v = \n";
    // for (int i = 0; i < N; ++i) {
    //   for (int j = 0; j < N; ++j) cout << board[i][j];
    //   cout << '\n';
    // }

    if (v == E) {
      cout << "POSSIBLE\n";
      return;
    }

    // swap 2 rows
    for (int r1 = 0; r1 < N; ++r1) for (int r2 = r1 + 1; r2 < N; ++r2) {
      int w = v;
      for (int j = 0; j < N; ++j) {
        int u1 = r1 * N + j;
        int u2 = r2 * N + j;
        if (v & (1 << u1)) w |= (1 << u2);
        else w &= ~(1 << u2);
        if (v & (1 << u2)) w |= (1 << u1);
        else w &= ~(1 << u1);
      }
      if (vis.count(w)) continue;
      vis.insert(w);
      q.push(w);
    }

    // swap 2 columns
    for (int c1 = 0; c1 < N; ++c1) for (int c2 = c1 + 1; c2 < N; ++c2) {
      int w = v;
      for (int i = 0; i < N; ++i) {
        int u1 = i * N + c1;
        int u2 = i * N + c2;
        if (v & (1 << u1)) w |= (1 << u2);
        else w &= ~(1 << u2);
        if (v & (1 << u2)) w |= (1 << u1);
        else w &= ~(1 << u1);
      }
      if (vis.count(w)) continue;
      vis.insert(w);
      q.push(w);
    }
  }

  cout << "IMPOSSIBLE\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
