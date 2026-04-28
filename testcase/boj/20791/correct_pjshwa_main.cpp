#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5, MOD = 1e9 + 7;
ll a[MAX], b[MAX];

int n, x;
void solve() {
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < n; i++) cin >> b[i];

  ll ans = x;
  for (int i = 0; i < n; i++) ans = (ans + a[i] * b[i]) % MOD;
  for (int i = 0; i < n - 1; i++) ans = (ans * x) % MOD;
  cout << ans << '\n';
}

int main() {
  fast_io();

  while (cin >> n >> x) solve();
}
