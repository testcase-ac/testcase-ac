#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int sy, sm, sd, ey, em, ed;
  cin >> sy >> sm >> sd >> ey >> em >> ed;

  int period = (ey - sy) * 360 + (em - sm) * 30 + (ed - sd);
  int yt = period / 360, ybonus = 0;
  for (int i = 1; i <= yt; i++) ybonus += ((i - 1) / 2);
  int yf = 15 * yt + ybonus;
  int mf = min(period / 30, 36);
  cout << yf << ' ' << mf << '\n' << period << "days\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
