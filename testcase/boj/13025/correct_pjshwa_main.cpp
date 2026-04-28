#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll INF = 1e18;

void solve() {
  ll l, r, k;
  cin >> l >> r >> k;

  ll z = r - l + 1;
  if (z > 10) {
    if (k == 1) cout << l << '\n' << "1\n" << l << '\n';
    else if (k == 2) {
      for (ll i = l;; i++) {
        if (i % 2) continue;

        cout << "1\n2\n" << i << ' ' << i + 1 << '\n';
        break;
      }
    }
    else if (k == 3) {
      for (int b = 49; b >= 1; b--) {

        for (int p = b - 1; p >= 0; p--) {
          ll x = 0;
          ll y = (1LL << b);
          ll z = y;

          x += (1LL << (p + 1)) - 1;
          y += (1LL << p) - 1;
          z += (1LL << p);

          if (l <= x && x <= r && l <= y && y <= r && l <= z && z <= r) {
            ll u = x ^ y ^ z;
            assert(u == 0);
            assert(x != y && y != z && z != x);
            cout << "0\n3\n" << x << ' ' << y << ' ' << z << '\n';
            return;
          }
        }

      }

      for (ll i = l;; i++) {
        if (i % 2) continue;

        cout << "1\n2\n" << i << ' ' << i + 1 << '\n';
        break;
      }

    }
    else {
      for (ll i = l;; i++) {
        if (i % 4) continue;

        cout << "0\n4\n" << i << ' ' << i + 1 << ' ' << i + 2 << ' ' << i + 3 << '\n';
        break;
      }
    }

  }
  else {
    ll ans = INF;
    for (int state = 1; state < (1 << z); state++) {
      if (__builtin_popcount(state) > k) continue;

      ll val = 0;
      for (int i = 0; i < z; i++) {
        if (state & (1 << i)) val ^= (l + i);
      }
      ans = min(ans, val);
    }

    cout << ans << '\n';
    for (int state = 1; state < (1 << z); state++) {
      if (__builtin_popcount(state) > k) continue;

      ll val = 0;
      for (int i = 0; i < z; i++) {
        if (state & (1 << i)) val ^= (l + i);
      }
      if (val != ans) continue;

      cout << __builtin_popcount(state) << '\n';
      for (int i = 0; i < z; i++) {
        if (state & (1 << i)) cout << (l + i) << ' ';
      }
      cout << '\n';

      break;
    }

  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
