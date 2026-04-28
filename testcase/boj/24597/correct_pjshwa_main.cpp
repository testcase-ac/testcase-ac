#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  string s;
  cin >> s;
  int n = s.size();

  string t1 = s.substr(0, n - 1), t2 = s.substr(1, n - 1);
  reverse(t1.begin(), t1.end());
  reverse(t2.begin(), t2.end());

  bool amatch = false, bmatch = false;
  s += s;
  for (int i = 0; i < n; i++) {
    if (s.substr(i, n - 1) == t1) amatch = true;
    if (s.substr(i, n - 1) == t2) bmatch = true;
  }

  cout << (amatch && bmatch) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
