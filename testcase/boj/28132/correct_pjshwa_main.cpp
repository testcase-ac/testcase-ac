#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  ll ans = 0;
  int xz = 0, yz = 0, az = 0;
  map<pii, int> t;
  for (int i = 1; i <= N; i++) {
    int x, y; cin >> x >> y;
    if (x == 0) {
      if (y == 0) {
        ans += i - 1;
        az++; xz++; yz++;
      }
      else {
        ans += yz;
        xz++;
      }
    }
    else if (y == 0) {
      ans += xz;
      yz++;
    }
    else {
      int g = __gcd(abs(x), abs(y));
      x /= g; y /= g;
      if (y > 0) x = -x, y = -y;
      ans += t[{-y, x}]; ans += az;

      if (x < 0) x = -x, y = -y;
      t[{x, y}]++;
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
