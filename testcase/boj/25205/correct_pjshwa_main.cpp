#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n; string s;
  cin >> n >> s;

  char c = s[n - 1];
  bool w = (
    c == 'q' || c == 'w' || c == 'e' || c == 'r' || c == 't' ||
    c == 'a' || c == 's' || c == 'd' || c == 'f' || c == 'g' ||
    c == 'z' || c == 'x' || c == 'c' || c == 'v'
  );
  cout << w << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
