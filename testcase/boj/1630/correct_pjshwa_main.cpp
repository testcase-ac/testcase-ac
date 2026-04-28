#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll lpow(ll x, ll y, ll m) {
  ll r = 1;
  x %= m;
  while (y) {
    if (y & 1) r = (r * x) % m;
    x = (x * x) % m;
    y >>= 1;
  }
  return r;
}

const int MAX = 1e6, MOD = 987654321;
ll lp[MAX + 1];
vector<int> pr;

void solve() {
  int n;
  cin >> n;

  ll ans = 1;
  for (int prime : pr) {
    if (prime > n) break;

    ll c = prime;
    int pow = 1;
    while (c <= n) {
      pow++;
      c *= prime;
    }

    ans = (ans * lpow(prime, pow - 1, MOD)) % MOD;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAX; j++)
      lp[i * pr[j]] = pr[j];
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
