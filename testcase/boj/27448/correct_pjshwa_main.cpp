#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 80;
char board[MAX + 1][MAX + 1];

void solve() {
  int N, M, F; cin >> N >> M >> F;
  for (int i = 0; i < N; i++) cin >> board[i];

  // Straight cut - right & left
  int ans = 0;
  for (int i = 1; i < N; i++) {
    // Blocked at least once
    bool f = 0;
    
    int streak1 = 0, streak2 = 0, acc = 0;
    for (int j = 0; j < M; j++) {
      if (board[i][j] == '#') {
        if (board[i - 1][j] == '#') f = 1, streak1 = 0;
        else streak1++, acc++;
      }
      else if (board[i - 1][j] == '#') streak1++, acc++;
    }

    if (f) {
      for (int j = M - 1; j >= 0; j--) {
        if (board[i][j] == '#') {
          if (board[i - 1][j] == '#') f = 1, streak2 = 0;
          else streak2++;
        }
        else if (board[i - 1][j] == '#') streak2++;
      }
    }

    if (streak1 > F) acc -= (streak1 - F);
    if (streak2 > F) acc -= (streak2 - F);
    ans += acc;
  }

  // Straight cut - up & down
  for (int j = 1; j < M; j++) {
    // Blocked at least once
    bool f = 0;
    
    int streak1 = 0, streak2 = 0, acc = 0;
    for (int i = 0; i < N; i++) {
      if (board[i][j] == '#') {
        if (board[i][j - 1] == '#') f = 1, streak1 = 0;
        else streak1++, acc++;
      }
      else if (board[i][j - 1] == '#') streak1++, acc++;
    }

    if (f) {
      for (int i = N - 1; i >= 0; i--) {
        if (board[i][j] == '#') {
          if (board[i][j - 1] == '#') f = 1, streak2 = 0;
          else streak2++;
        }
        else if (board[i][j - 1] == '#') streak2++;
      }
    }

    if (streak1 > F) acc -= (streak1 - F);
    if (streak2 > F) acc -= (streak2 - F);
    ans += acc;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
