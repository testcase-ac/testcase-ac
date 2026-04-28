#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

string s, t;

void solve() {
  int si = 0;
  for (int ti = 0; ti < t.size(); ti++) {
    if (si < s.size() && s[si] == t[ti]) si++;
  }
  if (si == s.size()) cout << "Yes\n";
  else cout << "No\n";
}

int main() {
  fast_io();

  while (cin >> s >> t) solve();
}
