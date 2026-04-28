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

ll f(ll n) {
  ll pow = 2;
  ll ans = 0;
  while (pow <= n) {
    ans += (n / pow) * (pow / 2);
    pow *= 2;
  }
  return ans + n;
}

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  ll a, b;
  cin >> a >> b;
  cout << f(b) - f(a - 1) << '\n';
}
