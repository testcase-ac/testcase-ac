#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n;
  cin >> n;

  set<string> u;
  for (int i = 0; i < n; i++) {
    string s, o;
    cin >> s, o = s;
    sort(s.begin(), s.end());

    if (u.count(s)) continue;
    cout << o << '\n';
    u.insert(s);
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
