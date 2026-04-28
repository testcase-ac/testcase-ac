#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 1e9 + 7;

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int n, m; cin >> n >> m;
  if (n == 1) {
    if (m == 1) cout << 1;
    else cout << 2;
  }
  else {
    if (m == 1) cout << 2;
    else cout << 2 * (n + m - 2);
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
