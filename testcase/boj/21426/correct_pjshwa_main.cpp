#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool is_prime(ll n) {
  if (n <= 1) return false;
  if (n == 2) return true;
  if (n % 2 == 0) return false;

  for (ll i = 3; i * i <= n; i += 2) {
    if (n % i == 0) return false;
  }
  return true;
}

void solve() {
  ll a, b, c, d;
  cin >> a >> b >> c >> d;
  if (c < a) swap(a, c), swap(b, d);
  if (a > 1) return cout << a * c + 1 << '\n', void();

  if (c == 1) {
    ll ulim = max(b, d) + 1;
    while (!is_prime(ulim)) ulim++;
    for (ll i = max(b, d) + 1; i <= ulim; i++) {
      bool f = false;
      for (int j = a; j <= b; j++) {
        if (i % j) continue;

        ll k = i / j;
        if (c <= k && k <= d) {
          f = true;
          break;
        }
      }
      if (!f) return cout << i << '\n', void();
    }
  }
  else {
    // answer could not be bigger than the prime number larger than d
    ll ulim = d + 1;
    while (!is_prime(ulim)) ulim++;
    for (ll i = d + 1; i <= ulim; i++) {
      bool f = false;
      for (int j = a; j <= b; j++) {
        if (i % j) continue;

        ll k = i / j;
        if (c <= k && k <= d) {
          f = true;
          break;
        }
      }
      if (!f) return cout << i << '\n', void();
    }
  }
  
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
