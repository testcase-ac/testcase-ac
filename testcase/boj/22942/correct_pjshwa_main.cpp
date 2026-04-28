#include <bits/stdc++.h>
using namespace std;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n;
  cin >> n;

  vector<tii> a;
  set<int> upos;
  for (int i = 0; i < n; i++) {
    int x, r;
    cin >> x >> r;
    a.push_back({x - r, -1, i});
    a.push_back({x + r, +1, i});
    upos.insert(x - r);
    upos.insert(x + r);
  }

  if (upos.size() != n * 2) return cout << "NO\n", void();

  sort(a.begin(), a.end());

  stack<int> u;
  for (int i = 0; i < 2 * n; i++) {
    auto [p, o, x] = a[i];
    if (o == -1) u.push(x);
    else if (u.top() == x) u.pop();
    else return cout << "NO\n", void();
  }

  cout << "YES\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
