#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll C(int n, int k) {
  ll ret = 1;
  for (int i = 1; i <= k; i++) {
    ret *= n - k + i;
    ret /= i;
  }
  return ret;
}

void solve() {
  int n, m, k;
  cin >> n >> m >> k;

  ll ans;
  if (k) {
    int im = k % m, in = (k - 1) / m + 1;
    if (im == 0) im = m;

    ans = C(in + im - 2, in - 1) * C(n - in + m - im, n - in);
  }
  else ans = C(n + m - 2, n - 1);

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
