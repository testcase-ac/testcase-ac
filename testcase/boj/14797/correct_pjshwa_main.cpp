#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 25;
char board[MAX + 1][MAX + 1];

bool is_alpha(char c) {
  return 'A' <= c && c <= 'Z';
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ":\n";

  int N, M; cin >> N >> M;
  for (int i = 0; i < N; i++) {
    cin >> board[i];
    
    char l;
    l = 0;
    for (int j = 0; j < M; j++) {
      if (board[i][j] == '?') {
        if (l) board[i][j] = l;
      }
      else l = board[i][j];
    }
    l = 0;
    for (int j = M - 1; j >= 0; j--) {
      if (board[i][j] == '?') {
        if (l) board[i][j] = l;
      }
      else l = board[i][j];
    }
  }

  for (int j = 0; j < M; j++) {
    char l;
    l = 0;
    for (int i = 0; i < N; i++) {
      if (board[i][j] == '?') {
        if (l) board[i][j] = l;
      }
      else l = board[i][j];
    }
    l = 0;
    for (int i = N - 1; i >= 0; i--) {
      if (board[i][j] == '?') {
        if (l) board[i][j] = l;
      }
      else l = board[i][j];
    }
  }

  for (int i = 0; i < N; i++) cout << board[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
