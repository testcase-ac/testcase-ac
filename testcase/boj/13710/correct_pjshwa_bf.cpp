#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int a[MAX + 1], pf[MAX + 1];

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i], pf[i] = pf[i - 1] ^ a[i];

  ll ans = 0;
  for (int i = 1; i <= n; i++) for (int j = i; j <= n; j++) {
    ans += (pf[j] ^ pf[i - 1]);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
