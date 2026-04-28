#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  string s;
  cin >> s;
  int n = s.size();

  set<string> u;
  for (int i = 0; i < n; i++) {
    string t = "";
    for (int z = i; z < n; z++) {
      t += s[z];
      u.insert(t);
    }
  }

  cout << u.size() << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
