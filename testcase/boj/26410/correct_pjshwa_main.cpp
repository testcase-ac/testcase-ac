#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 0x3f3f3f3f;

void solve() {
  int n; cin >> n;
  int minx = INF, miny = INF;
  for (int i = 0; i < n; i++) {
    int x, y; cin >> x >> y;
    minx = min(minx, x);
    miny = min(miny, y);
  }
  cout << minx << ' ' << miny << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
