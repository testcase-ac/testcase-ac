#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50;
char board[MAX + 1][MAX + 1];
int N;

int get_score() {
  int res = 0;
  for (int i = 0; i < N; i++) {
    int last = 0, streak = 0;
    for (int j = 0; j < N; j++) {
      if (last == board[i][j]) streak++;
      else {
        res = max(res, streak);
        streak = 1;
        last = board[i][j];
      }
    }
    res = max(res, streak);
  }
  for (int j = 0; j < N; j++) {
    int last = 0, streak = 0;
    for (int i = 0; i < N; i++) {
      if (last == board[i][j]) streak++;
      else {
        res = max(res, streak);
        streak = 1;
        last = board[i][j];
      }
    }
    res = max(res, streak);
  }
  return res;
}

void solve() {
  cin >> N;
  for (int i = 0; i < N; i++) cin >> board[i];

  int ans = 0;
  for (int i = 0; i < N; i++) for (int j = 0; j < N - 1; j++) {
    if (board[i][j] == board[i][j + 1]) continue;
    swap(board[i][j], board[i][j + 1]);
    ans = max(ans, get_score());
    swap(board[i][j], board[i][j + 1]);
  }
  for (int i = 0; i < N - 1; i++) for (int j = 0; j < N; j++) {
    if (board[i][j] == board[i + 1][j]) continue;
    swap(board[i][j], board[i + 1][j]);
    ans = max(ans, get_score());
    swap(board[i][j], board[i + 1][j]);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
