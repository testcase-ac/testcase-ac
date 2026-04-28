#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000, MOD = 998'244'353;
ll a[MAX + 1], b[MAX + 1];

void solve() {
  int n, k;
  cin >> n >> k;

  map<int, int> t;
  for (int i = 0, x; i < n; i++) cin >> x, t[x]++;

  a[0] = 1;
  for (auto [_, v] : t) {
    b[0] = a[0];
    for (int i = 1; i <= k; i++) b[i] = (a[i - 1] * v) % MOD;
    for (int i = 1; i <= k; i++) b[i] = (b[i] + a[i]) % MOD;
    for (int i = 0; i <= k; i++) a[i] = b[i];
  }

  cout << a[k] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
