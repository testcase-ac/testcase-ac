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

ll exponial(ll n, ll mod) {
  if (n == 1 || mod == 1) return 1 % mod;
  if (n <= 5) return lpow(n, exponial(n - 1, mod), mod);

  // A^B is congruent to A^((B mod phi(C)) + phi(C)) mod C
  return lpow(n, exponial(n - 1, phi(mod)) + phi(mod), mod);
}

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  ll n, m;
  cin >> n >> m;
  cout << exponial(n, m) << '\n';
}
