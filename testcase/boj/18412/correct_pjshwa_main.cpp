#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, a, b; string s;
  cin >> n >> a >> b >> s;
  a--; b--;

  reverse(s.begin() + a, s.begin() + b + 1);
  cout << s << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
