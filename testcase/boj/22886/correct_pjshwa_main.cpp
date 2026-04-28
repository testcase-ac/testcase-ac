#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int INF = 0x3f3f3f3f;

// d[i][j] = min price of string ending at pos i, with character C (j = 0) or J (j = 1)
int d[1000][2], x, y;
string s;

void dp_init() {
  for (int i = 0; i < 1000; i++) for (int j = 0; j < 2; j++) d[i][j] = -INF;
}

int r(int i, int c) {
  if (i == 0) return 0;
  if (d[i][c] != -INF) return d[i][c];

  int ans;
  if (s[i - 1] == '?') {
    if (c == 0) ans = min(r(i - 1, 1) + y, r(i - 1, 0));
    else ans = min(r(i - 1, 1), r(i - 1, 0) + x);
  }
  else {
    if (s[i - 1] == 'C' && c == 1) ans = r(i - 1, 0) + x;
    else if (s[i - 1] == 'J' && c == 0) ans = r(i - 1, 1) + y;
    else ans = r(i - 1, c);
  }

  return d[i][c] = ans;
}

int main() {
  fast_io();

  int t;
  cin >> t;

  for (int tc = 1; tc <= t; tc++) {
    cin >> x >> y >> s;
    dp_init();

    int sz = s.size(), res;
    if (s[sz - 1] == '?') res = min(r(sz - 1, 0), r(sz - 1, 1));
    else res = r(sz - 1, s[sz - 1] == 'J');

    cout << "Case #" << tc << ": " << res << '\n';
  }

}
