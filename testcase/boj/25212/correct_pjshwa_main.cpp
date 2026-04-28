#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 10;
int a[MAX];

void solve() {
  int n;
  cin >> n;
  for (int j = 0; j < n; j++) cin >> a[j];

  ll denom = 26771144400LL, ans = 0;
  for (int i = 0; i < (1 << n); i++) {
    ll nom = 0;
    for (int j = 0; j < n; j++) {
      if (i & (1 << j)) nom += denom / a[j];
    }

    if (nom * 100 >= 99 * denom && nom * 100 <= 101 * denom) ans++;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
