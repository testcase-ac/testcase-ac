#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int t; cin >> t;

  cout << "2 5\n";
  cout << "a b c\n";
  cout << "a d e\n";
  cout << "b f g\n";
  cout << "h i j\n";

  if (t == 2) cout << "f g h\n";
  else cout << "c h i\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
