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

map<int, int> dp[1001][1001];
ll f(ll a, ll b, ll mod) {
  if (b == 1) return lpow(a, a, mod);
  if (a == 2 && b == 2) return 256 % mod;

  if (!dp[a][b].count(mod)) {

    // A^B is congruent to A^((B mod phi(C)) + phi(C)) mod C
    ll j = f(a, b - 1, mod);
    dp[a][b][mod] = lpow(j, f(a, b - 1, phi(mod)) + phi(mod), mod);
  }

  return dp[a][b][mod];
}

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int t;
  cin >> t;

  for (int iter = 1; iter <= t; iter++) {
    ll a, b, c;
    cin >> a >> b >> c;
    cout << "Case #" << iter << ": " << f(a, b, c) << '\n';
  }
}
