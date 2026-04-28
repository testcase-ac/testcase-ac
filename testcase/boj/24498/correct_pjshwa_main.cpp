#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int a[MAX];

void solve() {
  int n;
  cin >> n;

  int ans = 0;
  for (int i = 0; i < n; i++) cin >> a[i], ans = max(ans, a[i]);
  for (int i = 1; i < n - 1; i++) {
    ans = max(ans, a[i] + min(a[i - 1], a[i + 1]));
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
