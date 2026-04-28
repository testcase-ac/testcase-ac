#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll f(int x, int y, int i) {
  ll ret = (abs(x) + 1) ^ (abs(y) + 1);
  return ret * i + i;
}

void solve() {
  int n; string s; cin >> n >> s;

  for (int c = 0; c < n; ++c) {
    ll x = 0, y = 0, acc = 1;
    map<pii, int> V; V[{0, 0}] = 1;
    for (int i = 0; i < n; ++i) {
      if (i == c) continue;

      if (s[i] == 'L') --y;
      else if (s[i] == 'R') ++y;
      else if (s[i] == 'U') ++x;
      else --x;

      acc += f(x, y, ++V[{x, y}]);
    }

    cout << acc << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
