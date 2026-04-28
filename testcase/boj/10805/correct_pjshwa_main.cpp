#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int INF = 1e9 + 7;

int d[51][51];
int r(int n, int m) {
  if (n == 0 || m == 0) return 0;
  if (d[n][m] != -1) return d[n][m];
  if (n == 1) return d[n][m] = m;
  if (m == 1) return d[n][m] = n;
  if (n == m) return d[n][m] = 1;

  int ans = INF;
  for (int d = 1; d <= (n + 1) / 2; d++) ans = min(ans, r(n - d, m) + r(d, m));
  for (int d = 1; d <= (m + 1) / 2; d++) ans = min(ans, r(n, m - d) + r(n, d));
  return d[n][m] = ans;
}

int dl[51][51][51][51];
int q(int h1, int w1, int h2, int w2) {
  if (h2 == 0 || w2 == 0) return r(h1, w1);
  if (dl[h1][w1][h2][w2] != -1) return dl[h1][w1][h2][w2];

  int ans = INF;
  for (int d = 1; d <= w1 - 1; d++) {
    if (d + w2 < w1) ans = min(ans, r(h1, d) + q(h1, w1 - d, h2, w2));
    else if (d + w2 == w1) ans = min(ans, r(h1, d) + r(h1 - h2, w2));
    else ans = min(ans, r(w1 - d, h1 - h2) + q(h1, d, h2, w2 - (w1 - d)));
  }
  for (int d = 1; d <= h1 - 1; d++) {
    if (d < h2) ans = min(ans, r(d, w1 - w2) + q(h1 - d, w1, h2 - d, w2));
    else if (d == h2) ans = min(ans, r(w1 - w2, h2) + r(w1, h1 - h2));
    else ans = min(ans, r(h1 - d, w1) + q(d, w1, h2, w2));
  }
  return dl[h1][w1][h2][w2] = ans;
}

int main() {
  fast_io();

  int h1, w1, h2, w2;
  cin >> h1 >> w1 >> h2 >> w2;
  memset(d, -1, sizeof(d));
  memset(dl, -1, sizeof(dl));
  cout << q(h1, w1, h2, w2) << '\n';
}
