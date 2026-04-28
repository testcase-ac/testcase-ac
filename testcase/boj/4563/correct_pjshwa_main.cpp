#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll a;

void solve() {
  ll t = a * a;
  int ans = 0;
  for (int i = 1; i <= a; i++) {
    if (t % i == 0) {
      ll lc = i, rc = t / i;
      if ((lc + rc) & 1) continue;

      ll c = (lc + rc) / 2, b = max(lc, rc) - c;
      if (b > a) ans++;
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  while (1) {
    cin >> a;
    if (a == 0) break;
    solve();
  }
}
