#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int tc;

void solve(int b, int n) {
  map<int, int> t;
  int db = b;
  for (int i = 2; i <= b; i++) {
    while (db % i == 0) {
      db /= i;
      t[i]++;
    }
  }

  ll ans = 9e18;
  for (auto [k, v] : t) {
    ll p = k;

    ll cur = 0;
    while (p <= n) {
      cur += (n / p);
      p *= k;
    }

    ans = min(ans, cur / v);
  }

  cout << "Scenario #" << ++tc << ":\n" << ans << "\n\n";
}

int main() {
  fast_io();

  int t;
  cin >> t;
  while (t--) {
    int b, n;
    cin >> b >> n;
    solve(b, n);
  }
}
