#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int s[26] = {}, t[26] = {};

  string S;
  cin >> S;
  for (auto c : S) s[c - 'a'] ^= 1, t[c - 'a'] = 1;

  bool az = true, ao = true;
  for (int i = 0; i < 26; ++i) {
    if (!t[i]) continue;
    if (s[i]) az = false;
    else ao = false;
  }

  if (az) cout << "0\n";
  else if (ao) cout << "1\n";
  else cout << "2\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
