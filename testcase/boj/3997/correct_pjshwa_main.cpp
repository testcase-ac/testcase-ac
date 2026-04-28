#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n; string s;
  cin >> n >> s;

  map<ll, int> t;
  t[0] = 1;

  ll state = 0, ans = 0;
  for (int i = 0; i < n; i++) {
    ll u;
    if (s[i] >= 'a') u = 1LL << (s[i] - 'a');
    else u = 1LL << (s[i] - 'A' + 26);

    state ^= u;
    ans += t[state];
    for (int j = 0; j < 52; j++) {
      ll nstate = state ^ (1LL << j);
      if (t.count(nstate)) ans += t[nstate];
    }
    t[state]++;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
