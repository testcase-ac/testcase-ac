#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5e5, MOD = 1e9 + 7;
int a[MAX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  ll l = 0, ans = 0;
  for (int i = 0; i < n; i++) {
    ans = (ans + l * a[i]) % MOD;
    l = (l + a[i]) % MOD;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
