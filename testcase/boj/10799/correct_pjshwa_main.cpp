#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  string s;
  cin >> s;

  int n = s.size(), pw = 0, ans = 0;
  for (int i = 0; i < n; i++) {
    char c = s[i];
    if (c == '(') pw++;
    else {
      pw--;
      if (s[i - 1] == '(') ans += pw;
      else ans++;
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
