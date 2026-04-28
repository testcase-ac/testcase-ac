#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  string s;
  cin >> s;
  s += s;

  int xm = 1, ym = 1;
  int d[3] = {-1, -1, 0};
  for (int i = 0; i < s.size(); i++) {
    d[0] = d[1], d[1] = d[2];
    if (s[i] == 'L') d[2] = (d[2] + 1) % 4;
    else d[2] = (d[2] + 3) % 4;

    if (d[0] == 1 && d[1] == 0 && d[2] == 3) ym = 0;
    if (d[0] == 3 && d[1] == 2 && d[2] == 1) ym = 0;
    if (d[0] == 0 && d[1] == 3 && d[2] == 2) xm = 0;
    if (d[0] == 2 && d[1] == 1 && d[2] == 0) xm = 0;
  }

  cout << xm + ym << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
