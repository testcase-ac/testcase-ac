#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, k; string s;
  cin >> n >> k >> s;

  map<ll, int> u;
  u[0] = -1;
  ll state = 0, ans = 0;
  for (ll i = 0; i < n; i++) {
    if (s[i] == 'O') state++;
    else state -= k;

    if (u.count(state)) ans = max(ans, i - u[state]);
    else u[state] = i;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
