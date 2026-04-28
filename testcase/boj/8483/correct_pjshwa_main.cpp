#include <bits/stdc++.h>
#define ll long long
#define pll pair<ll, ll>
using namespace std;

pll ext_gcd(ll a, ll b){
  if (b) {
    auto tmp = ext_gcd(b, a % b);
    return {tmp.second, tmp.first - (a / b) * tmp.second};
  } else return {1, 0};
}

bool able(ll a, ll b, ll s) {
  if (a == 0) {
    if (b == 0) return s == 0;
    else return s % b == 0;
  }
  if (b == 0) return s % a == 0;

  ll g = __gcd(a, b);
  if (s % g) return false;

  // a /= g; b /= g; s /= g;
  s /= g;
  auto[x, y] = ext_gcd(a, b);
  cout << x << ' ' << y << ' ' << s << endl;
  x *= s; y *= s;

  cout << x << ' ' << y << endl;

  // for (ll k = -x / b0; k <= y / a0; k++) {
  //   if (x + k * b0 < 0 || y - k * a0 < 0) continue;
  //   if (__gcd(x + k * b0, y - k * a0) == 1) return true;
  // }

  return false;
}

int main() {
  ll a, b, s;
  cin >> a >> b >> s;

  if (able(a, b, s)) cout << "YES\n";
  else cout << "NO\n";
}
