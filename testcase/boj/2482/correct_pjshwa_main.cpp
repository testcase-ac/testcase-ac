#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MOD = 1e9 + 3;
int d[1001][1001];
int r(int n, int k) {
  if (n < 0) return 0;
  if (k == 0) return 1;
  if (k == 1) return n;

  if (d[n][k] == -1) d[n][k] = (r(n - 1, k) + r(n - 2, k - 1)) % MOD;
  return d[n][k];
}

int main() {
  fast_io();

  int n, k;
  cin >> n >> k;
  memset(d, -1, sizeof(d));
  cout << (r(n - 1, k) + r(n - 3, k - 1)) % MOD;
}
