#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

const int MOD = 1e9;
int d[5001];
int main() {
  fast_io();

  int n, k;
  cin >> n >> k;

  d[0] = 1;
  for (int i = 1; i <= k; i++)
    for (int j = 1; j <= n; j++)
      d[j] = (d[j - 1] + d[j]) % MOD;

  cout << d[n] << '\n';
}
