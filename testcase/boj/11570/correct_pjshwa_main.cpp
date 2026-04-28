#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2000, INF = 1e9 + 7;
int a[MAX + 1];
int d[MAX + 10][MAX + 10];

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int i = 0; i <= n; i++) for (int j = 0; j <= n; j++) d[i][j] = INF;

  // Player A's last song is i
  // Player B's last song is j
  d[0][1] = d[1][0] = 0;
  for (int i = 0; i <= n; i++) for (int j = 0; j <= n; j++) {
    int cur = max(i, j), addend;
    addend = i == 0 ? 0 : abs(a[cur + 1] - a[i]);
    d[cur + 1][j] = min(d[cur + 1][j], d[i][j] + addend);
    addend = j == 0 ? 0 : abs(a[cur + 1] - a[j]);
    d[i][cur + 1] = min(d[i][cur + 1], d[i][j] + addend);
  }

  int ans = INF;
  for (int i = 0; i <= n; i++) ans = min({ans, d[i][n], d[n][i]});
  cout << ans << '\n';
}
