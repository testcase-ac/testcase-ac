#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];

  if (a[2] - a[1] == a[1] - a[0]) {
    int d = a[1] - a[0];
    cout << a[n - 1] + d << '\n';
  }
  else {
    int d = a[1] / a[0];
    cout << a[n - 1] * d << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
