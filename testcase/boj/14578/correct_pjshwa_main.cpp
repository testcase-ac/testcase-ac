#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5, MOD = 1e9 + 7;
ll a[MAX + 1], f[MAX + 1];

void solve() {
  int n;
  cin >> n;
  cout << (a[n] * f[n]) % MOD << '\n';
}

int main() {
  fast_io();

  a[0] = f[0] = 1;
  for (int i = 1; i <= MAX; i++) {
    a[i] = (i * a[i - 1] + ((i & 1) ? -1 : 1)) % MOD;
    f[i] = (f[i - 1] * i) % MOD;
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
