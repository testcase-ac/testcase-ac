#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void halt() {
  cout << "-1\n";
  exit(0);
}

int a, b;
int r(int c, int d) {
  if (c == a && d == b) return 0;
  if (c < a || d < b) halt();

  bool codd = c & 1, dodd = d & 1;
  
  if (codd != dodd) {
    if (c >= a && c - a == d - b) return c - a;
    else halt();
  }

  if (
    a <= c / 2 &&
    b <= d / 2 &&
    2 * abs(b - a) <= abs(d - c)
  ) {
    if (codd) return r((c - 1) / 2, (d - 1) / 2) + 2;
    else return r(c / 2, d / 2) + 1;
  }
  else {
    if (c >= a && c - a == d - b) return c - a;
    else halt();
  }
}

void solve() {
  int c, d;
  cin >> a >> b >> c >> d;
  cout << r(c, d) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
