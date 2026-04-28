#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n;
  string s;
  cin >> n >> s;
  map<int, int> m;
  m[0] = 1;

  int dt = 0;
  ll ans = 0;
  for (char c : s) {
    if (c == 'a') dt++;
    else dt--;
    ans += m[dt];
    m[dt]++;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
