#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int m, n;
  cin >> m >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    int r, c;
    cin >> r >> c;
    a[i] = r * c;
  }
  sort(a.begin(), a.end());
  reverse(a.begin(), a.end());

  int sum = 0;
  for (int i = 0; i < n; i++) {
    sum += a[i];
    if (sum >= m) return cout << i + 1 << '\n', void();
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
