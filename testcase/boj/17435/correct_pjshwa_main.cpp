#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int f[200'001][21];
int main() {
  fast_io();

  int n, m, x, y;
  cin >> n;

  for (int i = 1; i <= n; i++) cin >> f[i][0];
  for (int j = 0; j < 20; j++)
    for (int i = 1; i <= n; i++) f[i][j + 1] = f[f[i][j]][j];

  cin >> m;
  while (m--) {
    cin >> x >> y;
    for (int i = 0; x; i++) {
      if (x & 1) y = f[y][i];
      x >>= 1;
    }
    cout << y << '\n';
  }
}
