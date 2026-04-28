#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

const int MAX = 100;
int d[2][MAX + 1][MAX + 1][MAX + 1];
tii p[MAX + 1];

int main() {
  fast_io();

  int n, a, b;
  cin >> n >> a >> b;
  for (int i = 1; i <= n; i++) {
    int pi, qi, ri, si;
    cin >> pi >> qi >> ri >> si;
    p[i] = make_tuple(max(pi, qi), ri, si);
  }

  for (int k = 1; k <= n; k++) for (int i = n; i >= 0; i--) for (int j = n; j >= 0; j--) {
    if (i + j > k) continue;

    auto [x, y, z] = p[k];
    if (i) d[0][i][j][k] = max(d[0][i][j][k], d[0][i - 1][j][k - 1] + z);
    if (i) d[0][i][j][k] = max(d[0][i][j][k], d[1][i - 1][j][k - 1] + z);

    if (j) d[0][i][j][k] = max(d[0][i][j][k], d[0][i][j - 1][k - 1] + x);
    if (j) d[0][i][j][k] = max(d[0][i][j][k], d[1][i][j - 1][k - 1] + x);

    if (i + j < k) d[1][i][j][k] = max(d[1][i][j][k], d[0][i][j][k - 1] + y);
  }

  int ans = 0;
  for (int i = 0; i <= a; i++) for (int j = b; j <= n; j++) {
    if (i + j <= n) ans = max({ans, d[0][i][j][n], d[1][i][j][n]});
  }
  cout << ans << '\n';
}
