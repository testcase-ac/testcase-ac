#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

const int MAX = 50;
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};
char board[MAX + 1][MAX + 1];
bool vis[MAX * MAX + 1][MAX][MAX];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

char ans[7][100];

void r(int d, int s, int e) {
  if (d == 7) return;
  if (s + 1 == e) return;

  int m = (s + e) / 2;
  for (int i = s; i < m; i++) ans[d][i] = 'A';
  for (int i = m; i < e; i++) ans[d][i] = 'B';
  r(d + 1, s, m);
  r(d + 1, m, e);
}

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < n - 1; j++) ans[i][j] = 'A';
    ans[i][n - 1] = 'B';
  }
  r(0, 0, n);
  for (int i = 0; i < 7; i++) cout << ans[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
