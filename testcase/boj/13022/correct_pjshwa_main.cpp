#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  string s;
  cin >> s;
  int n = s.size();

  int state = 0, sval = 0, cval = 0, i = 0;
  while (i < n) {
    char c = s[i];
    if (state == 0 && c == 'w') {
      sval = 0;
      while (i < n && s[i] == 'w') i++, sval++;
      state = 1;
    }
    else if (state == 1 && c == 'o') {
      cval = 0;
      while (i < n && s[i] == 'o') i++, cval++;
      state = sval == cval ? 2 : 99;
    }
    else if (state == 2 && c == 'l') {
      cval = 0;
      while (i < n && s[i] == 'l') i++, cval++;
      state = sval == cval ? 3 : 99;
    }
    else if (state == 3 && c == 'f') {
      cval = 0;
      while (i < n && s[i] == 'f') i++, cval++;
      state = sval == cval ? 0 : 99;
    }
    else state = 99;

    if (state == 99) break;
  }

  cout << (state == 0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
