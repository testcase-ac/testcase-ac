#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e6;
int a[MAX], t[MAX];
int n;

void solve() {
  cin >> n;
  memset(t, 0, sizeof(t));
  for (int i = 0; i < n; ++i) cin >> a[i], t[a[i]]++;

  ll ans = 0;
  for (int i = 1; i <= 1e6; ++i) {
    for (int j = i; j <= 1e6; j += i) {
      int x = j ^ i;
      if (j < x && gcd(j, x) == i) ans += (ll)t[j] * t[x];
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t;
  cin >> t;
  while (t--) solve();
}
