#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 20;
int board[MAX][MAX];
bool d[MAX + 1][MAX + 1][40000];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> board[i][j];

  d[1][0][0] = 1;
  int b = 0;
  for (int i = 1; i <= n; i++) {
    b += board[n - i][0];
    d[1][i][b] = 1;
  }
  for (int j = 2; j <= n; j++) {
    int b = 0;
    for (int i = 0; i <= n; i++) {
      for (int w = 0; w <= 40000; w++) {
        if (w >= b) d[j][i][w] |= d[j - 1][i][w - b];
      }
      b += board[n - i][j - 1];
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
