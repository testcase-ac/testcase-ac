#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e4;
ll va[MAX + 1];

void solve() {
  ll a, b, c, d;
  cin >> a >> b >> c >> d;
  for (int i = b; i <= MAX; i++) {
    va[i] = max(d, a * (i - b) * (i - b) + c);
  }

  int ans = 0, Q;
  cin >> Q;
  while (Q--) {
    int ui, vi;
    cin >> ui >> vi;
    if (ui == va[vi]) ans++;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
