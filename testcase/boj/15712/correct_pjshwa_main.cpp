#include <bits/stdc++.h>
#define ll long long
using namespace std;

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

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

ll sum_geom_sec(ll a, ll r, ll n, ll mod) {
  ll ans;
  if (n == 1) ans = a;
  else {
    ans = 1 + lpow(r, n / 2, mod);
    ans *= sum_geom_sec(a, r, n / 2, mod);
    ans %= mod;
    if (n % 2 == 1) ans += (a * lpow(r, n - 1, mod)) % mod;
  }

  return ans % mod;
}

int main() {
  fast_io();

  ll a, r, n, mod;
  cin >> a >> r >> n >> mod;

  cout << sum_geom_sec(a, r, n, mod) << '\n';
}
