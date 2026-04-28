#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n; string s; cin >> n >> s;

  int wc = 0;
  for (int i = 0; i < n; i++) wc += s[i] == 'W';

  int ans = wc;
  for (int i = n; i < 2 * n - 1; i++) {
    if (s[i] == 'W') wc++;
    if (s[i - n] == 'W') wc--;
    ans = max(ans, wc);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
