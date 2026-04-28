#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
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

ll comb(ll n, ll r, ll mod) {
  if (r < 0 || r > n) return 0;
  if (n == 0) return r == 0;

  ll resn = 1;
  for (int i = 0; i < r; i++) {
    resn = (resn * (n - i)) % mod;
  }

  ll resm = 1;
  for (int i = 0; i < r; i++) {
    resm = (resm * (i + 1)) % mod;
  }

  return (resn * lpow(resm, mod - 2, mod)) % mod;
}

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;

  ll res;
  ll mod = 998244353;
  if (n & 1) res = (comb(n - 1, m + n / 2, mod) + comb(n - 1, m + n / 2 + 1, mod)) % mod;
  else res = comb(n, m + n / 2, mod);
  cout << res << '\n';
}
