#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MOD = 1e9 + 7;
int d[10001];
int main() {
  fast_io();

  int n, m;
  cin >> n >> m;
  for (int i = 0; i < min(n, m); i++) d[i] = 1;
  for (int i = min(n, m); i <= n; i++) d[i] = (d[i - 1] + d[i - m]) % MOD;
  cout << d[n];
}
