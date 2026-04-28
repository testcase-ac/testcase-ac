#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MOD = 1e9 + 7;
int d[3][1515];
int main() {
  fast_io();

  int n;
  cin >> n;

  d[1][1] = d[2][1] = 1;
  for (int i = 2; i < 1515; i++) {
    d[0][i] = (d[1][i - 1] + d[2][i - 1]) % MOD;
    d[1][i] = (d[0][i - 1] + d[2][i - 1]) % MOD;
    d[2][i] = (d[0][i - 1] + d[1][i - 1]) % MOD;
  }

  cout << d[1][n - 1] << '\n';
}
