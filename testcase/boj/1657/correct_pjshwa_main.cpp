#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

char board[15][15];
int price_table[6][6] = {
  {10, 8, 7, 5, 0, 1},
  {8, 6, 4, 3, 0, 1},
  {7, 4, 3, 2, 0, 1},
  {5, 3, 2, 2, 0, 1},
  {0, 0, 0, 0, 0, 0},
  {1, 1, 1, 1, 0, 0}
};

int price(char a, char b) {
  return price_table[a - 'A'][b - 'A'];
}

const int MAX = 14;
int d[MAX][MAX][1 << MAX];
int n, m;

pii next(pii cur) {
  auto [i, j] = cur;

  int ni, nj;
  if (j == m - 1) ni = i + 1, nj = 0;
  else ni = i, nj = j + 1;

  return {ni, nj};
}

int r(pii p, int b) {
  auto [i, j] = p;
  if (i == n && j == 0) return 0;

  b &= (1 << m) - 1;
  if (d[i][j][b] != -1) return d[i][j][b];

  int res = r(next(p), b << 1);
  if (j < m - 1 && (b & (1 << (m - 1))) == 0 && (b & (1 << (m - 2))) == 0) {
    res = max(res, r(next(p), (b << 1) | (1 << (m - 1))) + price(board[i][j], board[i][j + 1]));
  }
  if (i < n - 1 && (b & (1 << (m - 1))) == 0) {
    res = max(res, r(next(p), (b << 1) | 1) + price(board[i][j], board[i + 1][j]));
  }

  return d[i][j][b] = res;
}

void solve() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> board[i];
  memset(d, -1, sizeof(d));
  cout << r({0, 0}, 0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
