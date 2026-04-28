#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int tc;
void solve() {
  cout << "Grid #" << ++tc << ": ";

  int d, n; cin >> d >> n;
  if (d > (n - 1) * (n - 1) + 1) cout << "impossible\n";
  else cout << 2 * (n - 1) * d << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) {
    solve();
    if (t) cout << '\n';
  }
}
