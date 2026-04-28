#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S;
  while (cin >> S) {
    regex re("da+dd?(i|y)");
    if (regex_match(S, re)) cout << "She called me!!!\n"; 
    else cout << "Cooing\n"; 
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
