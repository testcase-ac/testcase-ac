#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100;
int board[MAX][MAX];

void solve() {
  int n, m, k; cin >> n >> m >> k;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> board[i][j];

  int max_hstreak = 0, max_vstreak = 0;
  for (int i = 0; i < n; i++) {
    int hstreak = 0;
    for (int j = 0; j < m; j++) {
      if (board[i][j] == 1) hstreak++;
      else hstreak = 0;
      max_hstreak = max(max_hstreak, hstreak);
    }
  }
  for (int j = 0; j < m; j++) {
    int vstreak = 0;
    for (int i = 0; i < n; i++) {
      if (board[i][j] == 1) vstreak++;
      else vstreak = 0;
      max_vstreak = max(max_vstreak, vstreak);
    }
  }

  if (k < max(max_hstreak, max_vstreak)) cout << "NO\n";
  else {
    cout << "YES\n";
    int A[n][m]{}; A[0][0] = 1;
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
      if (i == 0 && j == 0) continue;
      if (i) A[i][j] = max(A[i][j], A[i - 1][j] + 1);
      if (j) A[i][j] = max(A[i][j], A[i][j - 1] + 1);
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (board[i][j] == 0) A[i][j] = 0;
        else A[i][j] = (A[i][j] - 1) % k + 1;
        cout << A[i][j] << ' ';
      }
      cout << '\n';
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
