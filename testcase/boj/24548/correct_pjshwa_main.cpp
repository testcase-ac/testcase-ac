#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int t[81];

void solve() {
  int n;
  string s;
  cin >> n >> s;

  t[0]++;
  int tc = 0, gc = 0, fc = 0, pc = 0;
  ll ans = 0;
  for (int i = 0; i < n; ++i) {
    if (s[i] == 'T') tc++;
    if (s[i] == 'G') gc++;
    if (s[i] == 'F') fc++;
    if (s[i] == 'P') pc++;

    int state = 27 * (tc % 3) + 9 * (gc % 3) + 3 * (fc % 3) + pc % 3;
    ans += t[state];
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
