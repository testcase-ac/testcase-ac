#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 10, INF = 1e9 + 7;
int a[MAX + 1], d[MAX + 1][10001];

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) cin >> a[i];

  for (int i = 0; i <= n; i++) for (int j = 0; j <= 10000; j++) d[i][j] = INF;
  d[0][0] = 0;

  for (int i = 1; i <= n; i++) for (int j = 0; j <= 10000; j++) {
    for (int k = 0; k * k <= j; k++) {
      d[i][j] = min(d[i][j], d[i - 1][j - k * k] + (k - a[i]) * (k - a[i]));
    }
  }

  if (d[n][m] == INF) cout << -1 << '\n';
  else cout << d[n][m] << '\n';
}
