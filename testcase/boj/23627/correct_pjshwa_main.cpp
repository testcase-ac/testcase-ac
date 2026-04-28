#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  string s;
  cin >> s;
  int n = s.size();
  if (n < 5) cout << "not cute";
  else {
    if (s.substr(n - 5) == "driip") cout << "cute";
    else cout << "not cute";
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
