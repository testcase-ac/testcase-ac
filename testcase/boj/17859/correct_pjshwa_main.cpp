#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int a, b, c, d, e, f, g;
  cin >> a >> b >> c >> d >> e >> f >> g;

  priority_queue<int> sizes;
  for (int i = 1; i <= 100; i++) {
    if (a < 2 * i || b < 2 * i) break;
    sizes.push(i * (a - 2 * i) * (b - 2 * i));
  }

  int s1 = sizes.top(); sizes.pop();
  int s2 = sizes.top(); sizes.pop();
  int s3 = sizes.top(); sizes.pop();

  for (int i = 0;; i++) {
    ll w = (ll)s1 * i + c;
    if (w > g) break;
    if (w < f) continue;

    if (w % s2 == d && w % s3 == e) {
      cout << w << '\n';
      return;
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
