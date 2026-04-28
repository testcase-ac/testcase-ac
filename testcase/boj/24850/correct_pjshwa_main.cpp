#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  ll a, b;
  cin >> a >> b;

  vector<pll> ans;
  while (1) {
    if (a == 0 || b == 0) break;

    if (abs(a) > abs(b)) {
      ll k = -(a / b);

      a += k * b;
      if (k > 0) {
        if (abs(a) > abs(a + b)) {
          ans.push_back({1, k + 1});
          a += b;
        }
        else ans.push_back({1, k});
      }
      else {
        if (abs(a) > abs(a - b)) {
          ans.push_back({1, k - 1});
          a -= b;
        }
        else ans.push_back({1, k});
      }
    }
    else {
      ll k = -(b / a);

      b += k * a;
      if (k > 0) {
        if (abs(b) > abs(b + a)) {
          ans.push_back({2, k + 1});
          b += a;
        }
        else ans.push_back({2, k});
      }
      else {
        if (abs(b) > abs(b - a)) {
          ans.push_back({2, k - 1});
          b -= a;
        }
        else ans.push_back({2, k});
      }
    }

    // cout << "a = " << a << ", b = " << b << "\n";
  }

  cout << ans.size() << '\n';
  for (auto [x, y] : ans) cout << x << ' ' << y << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
