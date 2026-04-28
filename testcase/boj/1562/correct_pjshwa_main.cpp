#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll d[101][10][1 << 10];
ll mod = 1e9;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 1; i <= 9; i++) d[1][i][1 << i] = 1;
  for (int i = 1; i <= n - 1; i++) {
    for (int j = 0; j <= 9; j++) {
      for (int k = 0; k < (1 << 10); k++) {
        if (d[i][j][k] == 0) continue;
        if ((k & (1 << j)) == 0) continue;
        if (j + 1 <= 9) {
          d[i + 1][j + 1][k | (1 << (j + 1))] += d[i][j][k];
          d[i + 1][j + 1][k | (1 << (j + 1))] %= mod;
        }
        if (j - 1 >= 0) {
          d[i + 1][j - 1][k | (1 << (j - 1))] += d[i][j][k];
          d[i + 1][j - 1][k | (1 << (j - 1))] %= mod;
        }
      }
    }
  }

  ll ans = 0;
  for (int i = 0; i <= 9; i++) {
    ans += d[n][i][(1 << 10) - 1];
    ans %= mod;
  }
  cout << ans << '\n';
}
