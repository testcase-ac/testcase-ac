#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n;
  cin >> n;

  set<string> u;
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    u.insert(s);
  }
  cout << u.size() << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
