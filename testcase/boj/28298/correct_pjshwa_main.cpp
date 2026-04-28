#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 500;
char board[MAX + 1][MAX + 1];

void solve() {
  int N, M, K; cin >> N >> M >> K;
  for (int i = 0; i < N; i++) cin >> board[i];

  map<char, int> D[K][K];
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    int x = i % K, y = j % K;
    D[x][y][board[i][j]]++;
  }

  char ans[K][K];
  for (int i = 0; i < K; i++) for (int j = 0; j < K; j++) {
    int mx = 0;
    for (auto [c, cnt] : D[i][j]) {
      if (cnt > mx) mx = cnt, ans[i][j] = c;
    }
  }

  int cost = 0;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    int x = i % K, y = j % K;
    if (board[i][j] != ans[x][y]) cost++;
  }

  cout << cost << '\n';
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) cout << ans[i % K][j % K];
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
