#include <bits/stdc++.h>
using namespace std;

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

  int ans = 0;
  int sp = 0, ep = n - 1;
  while (sp < ep) {
    ans += 2 * a[ep];
    ep--;
    sp++;
  }
  if (sp == ep) ans += a[sp];

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
