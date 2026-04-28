#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

char board[3001][3001];
int wd[3001][3001], bd[3001][3001];

bool is_black(int i, int j) {
  return board[i][j] == (((i + j) % 2) ? 'W' : 'B');
}

bool is_white(int i, int j) {
  return !is_black(i, j);
}

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> board[i];

  for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
    if (is_black(i - 1, j - 1)) bd[i][j] = min({bd[i - 1][j], bd[i][j - 1], bd[i - 1][j - 1]}) + 1;
  }
  for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
    if (is_white(i - 1, j - 1)) wd[i][j] = min({wd[i - 1][j], wd[i][j - 1], wd[i - 1][j - 1]}) + 1;
  }

  ll ans = 0;
  for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
    ans += bd[i][j];
    ans += wd[i][j];
  }
  cout << ans;
}
