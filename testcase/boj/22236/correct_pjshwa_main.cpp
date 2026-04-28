#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2000;
ll d[MAX + 1];

int main() {
  fast_io();

  int n, MOD;
  cin >> n >> MOD;
  n = (n / 2) - 1;

  d[0] = d[1] = 1;
  for (int i = 2; i <= n; i++) {
    for (int j = 0; j < i; j++) d[i] = (d[i] + d[i - j - 1] * d[j]) % MOD;
  }
  cout << d[n] << '\n';
}
