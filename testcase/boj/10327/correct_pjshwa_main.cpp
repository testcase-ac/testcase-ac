#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

pll ext_gcd(ll a, ll b) {
  if (b) {
    auto tmp = ext_gcd(b, a % b);
    return {tmp.second, tmp.first - (a / b) * tmp.second};
  } else return {1, 0};
}

void solve() {
  ll N;
  cin >> N;

  ll a = 0, b = 1;
  pll ans = {1e18, 1e18};
  while (a <= N && b <= N) {
    auto [x, y] = ext_gcd(a, b);
    x *= N; y *= N;

    ll k = min(ceil((double)y / a), ceil((double)-x / b));
    x += b * k;
    y -= a * k;

    if (x >= 0 && y >= 0) {
      if (x > y || x == 0) {
        swap(x, y);
        y += x;
      }

      if (x > 0 && y > 0) {
        auto [ox, oy] = ans;
        if (oy > y || (oy == y && ox > x)) ans = {x, y};
      }
    }

    ll t = b;
    b += a;
    a = t;
  }

  auto [x, y] = ans;
  cout << x << ' ' << y << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
