#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll mobius[200001], mpf[200001];

void solve() {
  ll a, b, d, s;
  cin >> a >> b >> d;
  a /= d;
  b /= d;
  s = min(a, b);

  ll ans = 0, k = 1;
  while (k <= s) {
    int afin = a / (a / k), bfin = b / (b / k);
    int next = min(afin, bfin);
    ans += (mpf[next] - mpf[k - 1]) * (a / k) * (b / k);
    k = next + 1;
  }

  cout << ans << '\n';
}

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  // Precompute Mobius function values
  for (int i = 1; i <= 200000; i++) mobius[i] = 1;
  for (int i = 2; i * i <= 200000; i++) {
    if (mobius[i] == 1) {
      for (int j = i; j <= 200000; j += i) mobius[j] *= -i;
      for (int j = i * i; j <= 200000; j += i * i) mobius[j] = 0;
    }
  }
  for (int i = 2; i <= 200000; i++) {
    if (mobius[i] == i) mobius[i] = 1;
    else if (mobius[i] == -i) mobius[i] = -1;
    else if (mobius[i] < 0) mobius[i] = 1;
    else if (mobius[i] > 0) mobius[i] = -1;
  }
  mpf[1] = mobius[1];
  for (int i = 2; i <= 200000; i++) mpf[i] = mpf[i - 1] + mobius[i];

  int t;
  cin >> t;
  while (t--) solve();
}
