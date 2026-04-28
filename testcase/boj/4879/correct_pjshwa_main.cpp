#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll d[20][250];
int n, k;

void solve() {
  cout << d[n][k] << '\n';
}

int main() {
  fast_io();

  d[1][0] = 1;
  for (int i = 2; i <= 18; i++) {
    ll s = 0;
    for (int j = 0; j <= 200; j++) {
      s += d[i - 1][j];
      if (j >= i) s -= d[i - 1][j - i];
      d[i][j] = s;
    }
  }

  while (1) {
    cin >> n >> k;
    if (n == 0 && k == 0) break;
    solve();
  }
}
