#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6, MOD = 1e9 + 9;
ll d[MAX + 1];

int main() {
  fast_io();

  int n, k;
  cin >> n >> k;

  d[0] = 1;
  for (int i = 1; i <= n; ++i) {
    d[i] = k * d[i - 1] + 2 * (i < 5 ? 0 : MOD - d[i - 5]) + (i < 7 ? 0 : d[i - 7]);
    d[i] %= MOD;
  }
  cout << d[n] << '\n';
}
