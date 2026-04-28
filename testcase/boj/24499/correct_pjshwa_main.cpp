#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int a[MAX];

void solve() {
  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n; i++) cin >> a[i];

  int ans = 0, cur = 0;
  for (int i = 0; i < k; i++) cur += a[i];
  ans = max(ans, cur);

  for (int i = 0; i < n; i++) {
    cur += a[(i + k) % n] - a[i];
    ans = max(ans, cur);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
