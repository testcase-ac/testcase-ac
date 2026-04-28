#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
vector<int> by_val[MAX + 1];

bool query() {
  int n, l = 0; cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int x : a) {
    auto it = lower_bound(by_val[x].begin(), by_val[x].end(), l);
    if (it == by_val[x].end()) return false;
    l = *it + 1;
  }
  return true;
}

void solve() {
  int m; cin >> m;
  for (int i = 0; i < m; i++) {
    int x; cin >> x;
    by_val[x].push_back(i);
  }

  int q; cin >> q;
  for (int i = 0; i < q; i++) {
    cout << (query() ? "TAK" : "NIE") << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
