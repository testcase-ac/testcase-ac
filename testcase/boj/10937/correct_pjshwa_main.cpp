#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 11;
char board[MAX + 1][MAX + 1];
int price_table[4][4] = {
  {100, 70, 40, 0},
  {70, 50, 30, 0},
  {40, 30, 20, 0},
  {0, 0, 0, 0}
};

int price(char a, char b) {
  if (a == 'F' || b == 'F') return 0;
  return price_table[a - 'A'][b - 'A'];
}

int d[MAX][MAX][1 << MAX];
int n, m;

int r(int i, int j, int b) {
  if (i == n && j == 0) return 0;

  b &= (1 << m) - 1;
  if (d[i][j][b] != -1) return d[i][j][b];

  int ni, nj;
  if (j == m - 1) ni = i + 1, nj = 0;
  else ni = i, nj = j + 1;

  int res = r(ni, nj, b << 1);
  if (j < m - 1 && (b & (1 << (m - 1))) == 0 && (b & (1 << (m - 2))) == 0) {
    res = max(res, r(ni, nj, (b << 1) | (1 << (m - 1))) + price(board[i][j], board[i][j + 1]));
  }
  if (i < n - 1 && (b & (1 << (m - 1))) == 0) {
    res = max(res, r(ni, nj, (b << 1) | 1) + price(board[i][j], board[i + 1][j]));
  }

  return d[i][j][b] = res;
}

void solve() {
  cin >> n;
  m = n;
  for (int i = 0; i < n; i++) cin >> board[i];
  memset(d, -1, sizeof(d));
  cout << r(0, 0, 0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
