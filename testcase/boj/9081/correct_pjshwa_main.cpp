#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  string s, t;
  cin >> s;
  t = s;
  if (next_permutation(s.begin(), s.end())) cout << s << '\n';
  else cout << t << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
