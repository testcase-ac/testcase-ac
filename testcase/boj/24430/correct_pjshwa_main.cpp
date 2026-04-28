#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
int A[MAX + 1][MAX + 1], U[MAX + 1][MAX + 1];
pii d[MAX + 1][MAX + 1];

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) cin >> A[i][j];

  int m;
  cin >> m;
  while (m--) {
    int x, y;
    cin >> x >> y;
    U[x][y] = 1;
  }

  for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
    auto c = max(d[i - 1][j], d[i][j - 1]);
    c.first += A[i][j];
    c.second += U[i][j];
    d[i][j] = c;
  }

  auto [c, p] = d[n][n];
  cout << c << ' ' << p << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
