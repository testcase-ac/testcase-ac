#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
uint a[MAX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  uint ans = 0, mask = 0;
  for (int b = 31; b >= 0; --b) {
    mask = mask | (1 << b);
    set<uint> s;
    for (int i = 0; i < n; i++) s.insert(a[i] & mask);

    uint t = ans | (1 << b);
    for (int prefix : s) {
      if (s.count(t ^ prefix)) {
        ans = t;
        break;
      }
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
