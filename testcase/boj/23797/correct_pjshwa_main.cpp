#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  string s;
  cin >> s;

  int k = 0, p = 0, frogs = 0;
  for (char& c : s) {
    if (c == 'K') {
      if (p) p--, k++;
      else frogs++, k++;
    }
    if (c == 'P') {
      if (k) k--, p++;
      else frogs++, p++;
    }
  }
  cout << frogs << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
