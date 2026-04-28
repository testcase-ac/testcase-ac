#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int k, w, m;
  cin >> k >> w >> m;

  int diff = w - k;
  if (diff <= 0) cout << "0\n";
  else cout << (diff - 1) / m + 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
