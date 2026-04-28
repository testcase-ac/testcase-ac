#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
int c[MAX + 1];

void solve() {
  int n, m, v;
  cin >> n >> m >> v;
  for (int i = 1; i <= n; i++) cin >> c[i];

  int cyc = n - v + 1;
  while (m--) {
    int x, res;
    cin >> x;
    x++;

    if (x <= n) res = c[x];
    else res = c[(x - v) % cyc + v];

    cout << res << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
