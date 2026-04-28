#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  ll a, b;
  cin >> a >> b;

  int cnt = 0;
  for (ll i = 1; i * i <= b; i++) {
    if (i * i < a) continue;

    string s = to_string(i * i);
    reverse(s.begin(), s.end());
    if (s[0] == '0') continue;

    ll r = stoll(s), q = (ll)sqrt(r);
    if (q * q == r) cnt++;
  }

  cout << cnt << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
