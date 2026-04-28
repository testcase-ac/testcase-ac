#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  string s;
  cin >> s;
  int state = 0;
  for (char c : s) {
    if (state == 0) {
      if (c >= 'B' && c <= 'F') state = 1;
      else if (c == 'A') state = 2;
      else state = 99;
    }
    else if (state == 1) {
      if (c == 'A') state = 2;
      else state = 99;
    }
    else if (state == 2) {
      if (c == 'A') state = 2;
      else if (c == 'F') state = 3;
      else state = 99;
    }
    else if (state == 3) {
      if (c == 'F') state = 3;
      else if (c == 'C') state = 4;
      else state = 99;
    }
    else if (state == 4) {
      if (c == 'C') state = 4;
      else if (c >= 'A' && c <= 'F') state = 5;
      else state = 99;
    }
    else if (state == 5) state = 99;
  }

  cout << (state == 4 || state == 5 ? "Infected!" : "Good") << '\n';
}

int main() {
  fast_io();

  int t;
  cin >> t;
  while (t--) solve();
}
