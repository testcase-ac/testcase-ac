#include <bits/stdc++.h>
using namespace std;

const int MAX = 2000, MOD = 1e9 + 7;
int d[MAX][MAX + 1];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, l;
  cin >> n >> l;
  for (int i = 1; i <= n; i++) d[0][i] = 1;
  for (int cl = 1; cl < l; cl++) {
    for (int cn = 1; cn <= n; cn++) {
      for (int i = 1; i * i <= cn; i++) {
        if (cn % i == 0) {
          d[cl][cn] = (d[cl][cn] + d[cl - 1][i]) % MOD;
          if (i * i != cn) d[cl][cn] = (d[cl][cn] + d[cl - 1][cn / i]) % MOD;
        }
      }
    }
  }
  
  int ans = 0;
  for (int cn = 1; cn <= n; cn++) ans = (ans + d[l - 1][cn]) % MOD;
  cout << ans << '\n';
}
