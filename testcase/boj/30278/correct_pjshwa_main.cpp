#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll lcm(ll a, ll b) {
  return a / __gcd(a, b) * b;
}

void solve() {
  ll S, a, A, b, B; cin >> S >> a >> A >> b >> B;

  ll l = lcm(a, b), ans = 0;
  for (int acnt = 0; acnt <= l / a; ++acnt) {
    if (a * acnt > S) break;

    int bcnt = (S - a * acnt) / b;
    ans = max(ans, A * acnt + B * bcnt);
  }
  for (int bcnt = 0; bcnt <= l / b; ++bcnt) {
    if (b * bcnt > S) break;

    int acnt = (S - b * bcnt) / a;
    ans = max(ans, A * acnt + B * bcnt);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
