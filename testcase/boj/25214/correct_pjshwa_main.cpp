#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int INF = 1e9 + 7;

void solve() {
  int n;
  cin >> n;

  int cmin = INF, crun = 0;
  for (int i = 1; i <= n; i++) {
    int x;
    cin >> x;
    cmin = min(cmin, x);
    crun = max(crun, x - cmin);

    cout << crun << ' ';
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
