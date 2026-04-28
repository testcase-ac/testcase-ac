#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6, MOD = 1e9 + 9;
int d[MAX + 1];

void solve() {
  int n;
  cin >> n;
  cout << d[n] << '\n';
}

int main() {
  fast_io();

  d[0] = 1;
  for (int i = 1; i <= MAX; i++) {
    d[i] = d[i - 1];
    if (i >= 2) d[i] = (d[i] + d[i - 2]) % MOD;
    if (i >= 3) d[i] = (d[i] + d[i - 3]) % MOD;
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
