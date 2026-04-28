#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n;
  cin >> n;

  if (n == 1) return cout << "1\n", void();

  int gap = n / 2;
  for (int rem = gap; rem >= 1; rem--) {
    for (int base = 0; base + rem <= n; base += gap) cout << base + rem << ' ';
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
