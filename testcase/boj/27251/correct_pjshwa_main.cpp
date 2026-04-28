#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n; cin >> n;
  for (int i = 1; i <= n; i++) {
    if (i * i > 100) {
      for (int j = 1; j <= 100; j++) cout << '*';
      cout << "...";
    }
    else {
      for (int j = 1; j <= i * i; j++) cout << '*';
    }
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
