#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e4, MOD = 1e9 + 7;
int u[MAX], v[MAX];

void solve() {
  int n;
  ll m;
  string s;
  cin >> n >> m >> s;

  vector<int> a(n);
  int mt = 1e9;
  for (int i = 0; i < n; i++) a[i] = 25 - (s[i] - 'a'), mt = min(mt, a[i]);

  int ut = a[0];
  for (int i = 0; i <= a[0]; i++) u[i] = 1;
  for (int i = 1; i < n; i++) {
    memset(v, 0, sizeof(v));
    for (int j = 0; j <= a[i]; j++) {
      for (int k = 0; k <= ut; k++) v[k + j] += u[k];
    }
    ut += a[i];
    for (int k = 0; k <= ut; k++) u[k] = v[k];
  }

  int ans = 0;
  for (int i = mt; i <= min(m, (ll)ut); i++) ans = (ans + u[i]) % MOD;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
