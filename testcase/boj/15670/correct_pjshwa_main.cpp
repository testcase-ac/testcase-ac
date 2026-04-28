#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int a[MAX + 1], d[MAX + 1];

void solve() {
  int n, q;
  cin >> n >> q;
  for (int i = 1; i <= n; i++) cin >> a[i];

  for (int i = 2; i <= n; i++) {
    d[i] = d[i - 1];
    if (a[i] < a[i - 1]) d[i]++;
  }

  while (q--) {
    int l, r;
    cin >> l >> r;

    int res = d[n] + r - l - 2 * (d[r] - d[l]);
    if (r < n) {
      if (a[r] > a[r + 1] && a[l] < a[r + 1]) res--;
      if (a[r] < a[r + 1] && a[l] > a[r + 1]) res++;
    }
    if (l > 1) {
      if (a[l] > a[l - 1] && a[r] < a[l - 1]) res++;
      if (a[l] < a[l - 1] && a[r] > a[l - 1]) res--;
    }
    cout << res + 1 << '\n';
  }
}

int main() {
  fast_io();
 
  int t = 1;
  // cin >> t;
  while (t--) solve();
}
