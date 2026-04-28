#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2000;
char board[MAX + 1][MAX + 1];
int D[MAX][MAX];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; i++) cin >> board[i];

  for (int i = 0; i < N; i++) {
    char l;
    
    l = 0;
    for (int j = 0; j < N; j++) {
      if (l == 'O') D[i][j] = 1;
      if (board[i][j] != '.') l = board[i][j];
    }
    l = 0;
    for (int j = N - 1; j >= 0; j--) {
      if (l == 'O') D[i][j] = 1;
      if (board[i][j] != '.') l = board[i][j];
    }
  }

  for (int j = 0; j < N; j++) {
    char l;
    
    l = 0;
    for (int i = 0; i < N; i++) {
      if (l == 'O') D[i][j] = 1;
      if (board[i][j] != '.') l = board[i][j];
    }
    l = 0;
    for (int i = N - 1; i >= 0; i--) {
      if (l == 'O') D[i][j] = 1;
      if (board[i][j] != '.') l = board[i][j];
    }
  }

  for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
    if (board[i][j] == '.' && !D[i][j]) board[i][j] = 'B';
  }

  for (int i = 0; i < N; i++) cout << board[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
