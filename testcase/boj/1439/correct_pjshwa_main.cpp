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
  int n = s.size(), u = 0, d = 0;
  for (int i = 1; i < n; i++) {
    if (s[i - 1] < s[i]) u++;
    if (s[i - 1] > s[i]) d++;
  }
  cout << max(u, d) << "\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
