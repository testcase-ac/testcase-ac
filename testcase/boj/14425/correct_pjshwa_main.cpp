#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, m;
  cin >> n >> m;

  set<string> s;
  while (n--) {
    string x;
    cin >> x;
    s.insert(x);
  }

  int ans = 0;
  while (m--) {
    string x;
    cin >> x;
    if (s.count(x)) ans++;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
