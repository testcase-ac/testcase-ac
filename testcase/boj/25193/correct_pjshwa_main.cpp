#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n; string s;
  cin >> n >> s;

  int oc = n;
  for (char& c : s) {
    if (c == 'C') oc--;
  }

  for (int i = 0; i <= n; i++) {
    if (oc >= n / (i + 1)) return cout << i << '\n', void();
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
