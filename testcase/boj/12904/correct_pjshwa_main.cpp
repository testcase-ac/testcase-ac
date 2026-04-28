#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  string s, t;
  cin >> s >> t;

  int sz = s.size();
  int tz = t.size();
  int diff = tz - sz;
  int ori = 1;

  int lp = 0, rp = tz - 1;
  for (int i = 0; i < diff; i++) {
    if (ori == 1) {
      if (t[rp] == 'B') ori *= -1;
      rp--;
    }
    else {
      if (t[lp] == 'B') ori *= -1;
      lp++;
    }
  }

  t = t.substr(lp, rp - lp + 1);
  if (ori == -1) reverse(t.begin(), t.end());

  cout << (s == t) << '\n';
}
