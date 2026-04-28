#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n, m; cin >> n >> m;

  vector<int> candidates;
  for (int x = 1; x < m; ++x) {
    if ((n * x) % m == 1) candidates.push_back(x);
  }
  if (candidates.size() == 1) cout << candidates[0] << '\n';
  else cout << "No such integer exists.\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
