#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int a, b, n, m, x, l;
  cin >> a >> b >> n >> m;
  vector<int> hf(n), vf(m);
  vector<ll> hd(n + 1), vd(m + 1);

  for (int i = 0; i < n; i++) cin >> hf[i];
  for (int i = 0; i < m; i++) cin >> vf[i];
  sort(hf.begin(), hf.end());
  sort(vf.begin(), vf.end());

  l = 0;
  for (int i = 0; i < n; i++) {
    hd[i] = hf[i] - l;
    l = hf[i];
  }
  hd[n] = a - l;

  l = 0;
  for (int i = 0; i < m; i++) {
    vd[i] = vf[i] - l;
    l = vf[i];
  }
  vd[m] = b - l;

  sort(hd.begin(), hd.end());
  sort(vd.begin(), vd.end());

  ll ans = hd[0] * m + vd[0] * n;
  int i = 1, j = 1;
  while (i <= n && j <= m) {
    if (hd[i] < vd[j]) ans += hd[i++] * (m - j + 1);
    else ans += vd[j++] * (n - i + 1);
  }
  cout << ans << '\n';
}
