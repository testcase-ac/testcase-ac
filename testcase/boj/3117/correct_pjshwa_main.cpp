#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int f[100'001][31];
int q[100'000];
int main() {
  fast_io();

  int n, k, m;
  cin >> n >> k >> m;
  m--;

  for (int i = 0; i < n; i++) cin >> q[i];
  for (int i = 1; i <= k; i++) cin >> f[i][0];
  for (int j = 0; j < 29; j++)
    for (int i = 1; i <= k; i++) f[i][j + 1] = f[f[i][j]][j];

  int y, om = m;
  for (int i = 0; i < n; i++) {
    y = q[i];
    m = om;
    for (int i = 0; m; i++) {
      if (m & 1) y = f[y][i];
      m >>= 1;
    }
    cout << y << ' ';
  }
  cout << '\n';
}
