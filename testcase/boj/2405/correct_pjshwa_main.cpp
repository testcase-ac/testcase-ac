#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int a[MAX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a, a + n);

  ll ans = 0;
  for (int i = 1; i < n - 1; i++) {
    int mins = a[0] + a[i + 1], maxs = a[i - 1] + a[n - 1];
    ans = max(ans, abs((ll)mins - 2 * a[i]));
    ans = max(ans, abs((ll)maxs - 2 * a[i]));
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
