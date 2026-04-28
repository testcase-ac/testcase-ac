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

ll f(ll b, ll i, ll mod) {
  if (i == 1) return b % mod;
  if (i == 2) return lpow(b, b, mod);
  if (b == 2 && i == 3) return 16 % mod;
  if (b == 2 && i == 4) return 65536 % mod;

  // A^B is congruent to A^((B mod phi(C)) + phi(C)) mod C
  return lpow(b, f(b, i - 1, phi(mod)) + phi(mod), mod);
}

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  ll b, i, n, ans;
  string anss;

  while (1) {
    cin >> b;
    if (b == 0) return 0;
    cin >> i >> n;

    ans = f(b, i, lpow(10, n, 1e9));
    anss = to_string(ans);
    if (anss.size() < n) {
      for (int j = 0; j < n - anss.size(); j++) cout << '0';
    }
    cout << anss << '\n';
  }
}
