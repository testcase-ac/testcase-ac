#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 34;
ll board[MAX][MAX], d[MAX][MAX];
int n;

void solve() {
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    for (int j = 0; j < n; j++) board[i][j] = s[j] - '0';
  }

  memset(d, 0, sizeof(d));
  d[0][0] = 1;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    if (board[i][j] == 0) continue;
    if (i + board[i][j] < n) d[i + board[i][j]][j] += d[i][j];
    if (j + board[i][j] < n) d[i][j + board[i][j]] += d[i][j];
  }

  cout << d[n - 1][n - 1] << '\n';
}

int main() {
  fast_io();

  while (1) {
    cin >> n;
    if (n == -1) break;
    solve();
  }
}
