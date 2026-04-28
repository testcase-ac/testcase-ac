#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n;
  cin >> n;

  set<int> s{0};
  for (int i = 1; i <= n; i++) {
    int x;
    cin >> x;
    set<int> ns = s;
    for (int e : s) ns.insert((e + x) % 7);
    s = ns;
  }

  cout << (s.count(4) ? "YES" : "NO") << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
