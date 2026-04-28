#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
int a[MAX], d[MAX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i], d[i] = a[i];

  int ci = 0;
  while (ci < n) {
    int t = 30;
    while (t && ci < n) {
      int diff = min(d[ci], t);
      d[ci] -= diff;
      t -= diff;
      ci++;
    }
  }

  int ans = 0;
  for (int i = 0; i < n; i++) if (2 * (a[i] - d[i]) >= a[i]) ans++;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
