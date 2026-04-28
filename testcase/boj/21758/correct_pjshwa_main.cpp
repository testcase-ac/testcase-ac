#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int a[MAX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  int cur = 2 * accumulate(a + 2, a + n, 0), ans = cur;
  for (int i = 2; i < n - 1; i++) {
    cur += a[i - 1] - 2 * a[i];
    ans = max(ans, cur);
  }

  reverse(a, a + n);
  cur = 2 * accumulate(a + 2, a + n, 0), ans = max(ans, cur);
  for (int i = 2; i < n - 1; i++) {
    cur += a[i - 1] - 2 * a[i];
    ans = max(ans, cur);
  }

  cur = accumulate(a, a + n - 1, 0);
  for (int i = 1; i < n - 1; i++) {
    cur += a[i] - a[i - 1];
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
