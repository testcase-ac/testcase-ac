#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll nC2(int n) {
  return (ll)n * (n - 1) / 2;
}

void solve() {
  int n;
  string s;
  cin >> n >> s;

  ll ans = nC2(n);

  int l = 0;
  bool sw = false;
  for (int i = 0; i < n - 1; i++) {
    if (!sw && s[i] == s[i + 1]) {
      sw = true;
      ans -= nC2(i - l + 1);
    }
    if (sw && s[i] != s[i + 1]) {
      l = i;
      sw = false;
    }
  }
  if (!sw) ans -= nC2(n - l);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
