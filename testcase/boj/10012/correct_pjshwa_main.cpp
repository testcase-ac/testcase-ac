#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n;
  cin >> n;

  bool f = false;
  while (n % 2 == 0) {
    n /= 2;
    f = !f;
  }

  if (f) cout << "TAK\n";
  else cout << "NIE\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
