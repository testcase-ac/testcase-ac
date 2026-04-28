#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll LIM = 1e18;

void solve() {
  ll n, d; cin >> n >> d;
  ll g = __gcd(abs(n), d);
  n /= g; d /= g;

  for (ll w = 1;; w *= 2) {
    if (d == w) break;
    if (w > LIM) return cout << "-1\n", void();
  }

  bool sign = n < 0;
  n = abs(n); ll p = n / d, B = 1;
  n %= d;
  vector<char> ans; int wait = 0;
  while (p) {
    if (p & 1) ans.push_back('R');
    B *= 2; p /= 2;
    ans.push_back('U');
    ++wait;
  }
  while (wait--) {
    ans.push_back('D');
    B /= 2;
  }

  ll Bd = 1;
  while (n) {
    if (n >= d / Bd) {
      n -= d / Bd;
      ans.push_back('R');
    }
    Bd *= 2;
    ans.push_back('D');
  }
  ans.push_back('U');

  cout << ans.size() << '\n';
  for (auto& c : ans) {
    if (sign && c == 'R') cout << 'L';
    else cout << c;
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
