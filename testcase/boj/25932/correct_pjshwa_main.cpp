#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  bool f1 = false, f2 = false;
  for (int i = 0; i < 10; i++) {
    int x; cin >> x; cout << x << ' ';
    if (x == 17) f1 = true;
    if (x == 18) f2 = true;
  }

  cout << '\n';
  if (f1) {
    if (f2) cout << "both\n";
    else cout << "zack\n";
  }
  else {
    if (f2) cout << "mack\n";
    else cout << "none\n";
  }
}

int main() {
  fast_io();
 
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
    if (t) cout << '\n';
  }
}
