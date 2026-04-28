#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100, INF = 1e9 + 7;
int fpref[3][MAX + 1];
int d[MAX + 1][MAX + 1][MAX + 1][3];
int n;

int cost(int a, int b) {
  if (a < b) return min(b - a, a + n - b);
  else return min(a - b, b + n - a);
}

int f(int a, int b, int c, int l) {
  if (a == 0 && b == 0 && c == 0) return 0;
  if (d[a][b][c][l] != -1) return d[a][b][c][l];

  int ans = INF;
  if (l == 0 && a) {
    ans = min(ans, f(a - 1, b, c, 0) + cost(fpref[0][a], fpref[0][a - 1]));
    ans = min(ans, f(a - 1, b, c, 1) + cost(fpref[0][a], fpref[1][b]));
    ans = min(ans, f(a - 1, b, c, 2) + cost(fpref[0][a], fpref[2][c]));
  }
  if (l == 1 && b) {
    ans = min(ans, f(a, b - 1, c, 0) + cost(fpref[1][b], fpref[0][a]));
    ans = min(ans, f(a, b - 1, c, 1) + cost(fpref[1][b], fpref[1][b - 1]));
    ans = min(ans, f(a, b - 1, c, 2) + cost(fpref[1][b], fpref[2][c]));
  }
  if (l == 2 && c) {
    ans = min(ans, f(a, b, c - 1, 0) + cost(fpref[2][c], fpref[0][a]));
    ans = min(ans, f(a, b, c - 1, 1) + cost(fpref[2][c], fpref[1][b]));
    ans = min(ans, f(a, b, c - 1, 2) + cost(fpref[2][c], fpref[2][c - 1]));
  }
  return d[a][b][c][l] = ans;
}

void solve() {
  cin >> n;
  memset(d, -1, sizeof d);

  int a, b, c;
  cin >> a;
  for (int j = 1; j <= a; j++) cin >> fpref[0][j];
  cin >> b;
  for (int j = 1; j <= b; j++) {
    cin >> fpref[1][j];
    fpref[1][j] -= (n / 3);
    if (fpref[1][j] <= 0) fpref[1][j] += n;
  }
  cin >> c;
  for (int j = 1; j <= c; j++) {
    cin >> fpref[2][j];
    fpref[2][j] -= (n / 3) * 2;
    if (fpref[2][j] <= 0) fpref[2][j] += n;
  }

  fpref[0][0] = fpref[1][0] = fpref[2][0] = 1;
  cout << min({f(a, b, c, 0), f(a, b, c, 1), f(a, b, c, 2)}) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
