#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int INF = 1e9 + 7;
tii a[101];
int d[101][501][1001];

void solve() {
  int n, m, k;
  cin >> n >> m >> k;
  for (int i = 1; i <= n; i++) {
    int x, y, z;
    cin >> x >> y >> z;
    a[i] = {x, y, z};
  }

  for (int i = 0; i <= n; i++) for (int j = 0; j <= 500; j++) for (int l = 0; l <= 1000; l++) {
    d[i][j][l] = -INF;
  }
  d[0][0][0] = 0;

  for (int i = 1; i <= n; i++) {
    auto& [x, y, z] = a[i];

    for (int cp = 0; cp <= 500; cp++) for (int pc = 0; pc <= 1000; pc++) {
      d[i][cp][pc] = max(d[i][cp][pc], d[i - 1][cp][pc]);

      int cc = min(1000, pc + x);
      if (cp >= z) d[i][cp][cc] = max(d[i][cp][cc], d[i - 1][cp - z][pc] + y);
    }
  }

  for (int p = 0; p <= 500; p++) for (int c = m; c <= 1000; c++) {
    if (d[n][p][c] >= k) return cout << p << '\n', void();
  }
  cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
