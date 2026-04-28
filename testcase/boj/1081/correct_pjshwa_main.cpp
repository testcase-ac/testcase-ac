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

ll sum_digits_to(ll n, int dig) {
  if (dig == 1) return n * (n + 1) / 2;
  else {
    ll pow = lpow(10, dig - 1, 1e18);
    ll fdig = n / pow;
    ll rest = n % pow;
    ll ans = fdig * (fdig - 1) * pow / 2 + 45 * (dig - 1) * lpow(10, dig - 2, 1e18) * fdig + fdig * (rest + 1);
    return ans + sum_digits_to(rest, dig - 1);
  }
}

int main() {
  fast_io();

  ll l, u;
  cin >> l >> u;

  ll ldup = l, udup = u;
  int ldig = 0, udig = 0;

  while (l) {
    l /= 10;
    ldig++;
  }
  while (u) {
    u /= 10;
    udig++;
  }

  if (ldup) cout << sum_digits_to(udup, udig) - sum_digits_to(ldup - 1, ldig);
  else if (udup) cout << sum_digits_to(udup, udig);
  else cout << 0;
  cout << '\n';
}
