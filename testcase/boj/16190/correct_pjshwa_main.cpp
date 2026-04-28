#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX = 2000;
int a[MAX + 10], b[MAX + 10];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, px;
  cin >> n;
  for (int i = 1; i <= 2 * n; i++) cin >> a[i];
  cin >> px;

  bool f = true;
  int py = -1;
  for (int i = 2; i <= 2 * n; i++) {
    if (py == -1 && px >= a[i - 1]) {
      int cy = b[i - 1];
      for (int cx = a[i - 1]; cx <= a[i]; cx++) {
        if (cx == px) {
          py = cy;
          break;
        }

        if (f) cy++;
        else cy--;
      }
    }

    if (f) b[i] = b[i - 1] + a[i] - a[i - 1];
    else b[i] = b[i - 1] - a[i] + a[i - 1];
    
    f = !f;
  }

  int lx = a[2 * n] + b[2 * n];
  if (py == -1) {
    int cy = b[2 * n];
    for (int cx = a[2 * n]; cx <= lx; cx++) {
      if (cx == px) {
        py = cy;
        break;
      }
      cy--;
    }
  }

  ll ans = 0;
  for (int i = 2 * n; i >= 1; i--) {
    if (px <= a[i]) continue;

    ll dx = px - a[i], dy = py - b[i];
    double m = dy / (double)dx;

    double cy = m * (-px) + py;
    ans = max(ans, (ll)ceil(cy));
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
