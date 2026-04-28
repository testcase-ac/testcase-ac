#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2000;
bool s[MAX + 1][MAX + 1];

void solve() {
  int d1, d2;
  cin >> d1 >> d2;
  
  int ans = 0;
  for (int d = d1; d <= d2; d++) for (int i = 0; i < d; i++) {
    int g = __gcd(d, i);
    if (s[i / g][d / g]) continue;
    s[i / g][d / g] = true;
    ans++;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
