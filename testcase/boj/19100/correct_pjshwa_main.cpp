#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n, t; cin >> n >> t;
  vector<int> a(1 << n);
  for (int i = 0; i < (1 << n); i++) cin >> a[i];
  if (t & 1) reverse(a.begin(), a.end());
  for (int i = 0; i < (1 << n); i++) cout << a[i] << ' ';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
