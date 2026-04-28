#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll f[51];
void solve() {
  int n;
  cin >> n;

  for (int i = 0; i < n; i++) cin >> f[i], f[i]--;

  ll ans = 1;
  for (int i = n - 1; i >= 0; i--) {
    if (f[i] > 0) continue;

    ll dif = -f[i];
    f[i] += dif;
    ans += dif;
    for (int j = i - 1; j >= 0; j--) f[j] -= dif;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
