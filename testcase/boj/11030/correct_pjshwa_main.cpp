#include <bits/stdc++.h>
#define ll long long
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

ll f(ll a, ll b, ll mod) {
  if (b == 1) return a % mod;
  if (b == 2) return lpow(a, a, mod);
  if (a == 2 && b == 3) return 16 % mod;
  if (a == 2 && b == 4) return 65536 % mod;

  // A^B is congruent to A^((B mod phi(C)) + phi(C)) mod C
  return lpow(a, f(a, b - 1, phi(mod)) + phi(mod), mod);
}

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  ll a, b;
  cin >> a >> b;

  if (a == 1) cout << "1\n";
  else if (b == 1) cout << a << '\n';
  else if (
    (a == 2 && b <= 4) ||
    (a <= 7 && b == 2)
  ) cout << f(a, b, 1e8) << '\n';
  else {
    ll ans = f(a, b, 1e8);
    string anss = to_string(ans);
    if (anss.size() < 8) {
      for (int j = 0; j < 8 - anss.size(); j++) cout << '0';
    }
    cout << anss << '\n';
  }
}
