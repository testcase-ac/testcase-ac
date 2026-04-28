#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, m;
  cin >> n >> m;

  int tx, ty;
  vector<int> hs;
  for (int i = 0; i < n; i++) {
    int x, y, h;
    cin >> x >> y >> h;

    if (i == 0) {
      int g = abs(__gcd(x, y));
      tx = x / g, ty = y / g;
    }
    hs.push_back(h);
  }
  sort(hs.begin(), hs.end());

  ll acc = 0;
  while (m--) {
    int x, y, d;
    cin >> x >> y >> d;
    int g = abs(__gcd(x, y));

    if (tx == x / g && ty == y / g) acc += d;
    cout << hs.end() - upper_bound(hs.begin(), hs.end(), acc) << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
