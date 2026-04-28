#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

ll mul(ll x, ll y, ll m) {
  ll res = 0;
  while (y) {
    if (y % 2) res = (res + x) % m;
    x = (x * 2) % m;
    y /= 2;
  }
  return res;
}

ll lpow(ll x, ll y, ll m){
  ll r = 1;
  x %= m;
  while (y) {
    if (y & 1) r = mul(r, x, m);
    x = mul(x, x, m);
    y >>= 1;
  }
  return r;
}

int main() {
  fast_io();

  ll t, a, b, i, n, ans, dig;
  cin >> t;

  while (t--) {
    cin >> a >> b >> i >> n;

    for (ll k = i; k < i + n; k++) {
      ans = lpow(10, k - 1, b);
      ans = mul(ans, a, b);

      dig = 2 * (ans * 5 / b);
      ans = 2 * ((ans * 5) % b);
      dig += (ans / b);
      cout << dig;
    }
    cout << '\n';
  }
}
