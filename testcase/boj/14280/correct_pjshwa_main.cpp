#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int BIAS = 5e5;

ll a, b, c;
ll f(ll au, ll bu) {
  return abs(au) + abs(bu) + abs((a + au) * (b + bu) - c);
}

void solve() {
  cin >> a >> b >> c;

  ll ans = f(0, 0);
  for (ll d = -BIAS; d <= BIAS; d++) {
    if (a + d <= 0) continue;

    ll left = 1, right = 2e9;
    while (right - left >= 3) {
      ll mid1 = left + (right - left) / 3;
      ll mid2 = right - (right - left) / 3;
      if (f(d, mid1 - b) > f(d, mid2 - b)) left = mid1;
      else right = mid2;
    }

    for (ll i = left; i <= right; i++) ans = min(ans, f(d, i - b));

    ll A = a + d;
    ll Br = c / A;
    for (ll Ba = -10; Ba <= 10; Ba++) {
      ll B = Br + Ba;
      if (B <= 0) continue;
      ans = min(ans, abs(A - a) + abs(B - b) + abs(A * B - c));
    }
  }
  for (ll d = -BIAS; d <= BIAS; d++) {
    if (b + d <= 0) continue;

    ll left = 1, right = 2e9;
    while (right - left >= 3) {
      ll mid1 = left + (right - left) / 3;
      ll mid2 = right - (right - left) / 3;
      if (f(mid1 - a, d) > f(mid2 - a, d)) left = mid1;
      else right = mid2;
    }

    for (ll i = left; i <= right; i++) ans = min(ans, f(i - a, d));

    ll B = b + d;
    ll Ar = c / B;
    for (ll Aa = -10; Aa <= 10; Aa++) {
      ll A = Ar + Aa;
      if (A <= 0) continue;
      ans = min(ans, abs(A - a) + abs(B - b) + abs(A * B - c));
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
