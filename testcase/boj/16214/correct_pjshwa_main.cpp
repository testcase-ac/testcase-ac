#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll phi(ll n) {
  ll result = n;
  for (ll i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      while (n % i == 0) n /= i;
      result -= result / i;
    }
  }
  if (n > 1) result -= result / n;
  return result;
}

ll lpow(ll x, ll y, ll m){
  ll r = 1;
  x %= m;
  while (y) {
    if (y & 1) r = (r * x) % m;
    x = (x * x) % m;
    y >>= 1;
  }
  return r;
}

ll f(ll n, ll m) {
  if (m == 1 && n == 1) return 0;
  if (m == 1 || n == 1) return 1;

  // A^B is congruent to A^((B mod phi(C)) + phi(C)) mod C
  return lpow(n, f(n, phi(m)) + phi(m), m);
}

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  ll t, n, m;
  cin >> t;

  while (t--) {
    cin >> n >> m;
    cout << f(n, m) << '\n';
  }
}
