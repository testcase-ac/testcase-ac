#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n; string s;
  cin >> n >> s;

  int streak = 1;
  for (int i = 1; i < n; i++) {
    if (abs(s[i] - s[i - 1]) == 1) streak++;
    else streak = 1;

    if (streak == 5) return cout << "YES\n", void();
  }

  cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
