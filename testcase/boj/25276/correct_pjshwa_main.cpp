#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  string s1, s2;
  cin >> s1 >> s2;

  int w = s1.size() + s2.size();
  for (int i = 0; i < min(s1.size(), s2.size()); i++) {
    if (s1[i] == s2[i]) w -= 2;
    else break;
  }

  cout << w << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
