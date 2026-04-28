#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int c[3], m[3], y[3], k[3];
  for (int i = 0; i < 3; i++) cin >> c[i] >> m[i] >> y[i] >> k[i];

  int cm = *min_element(c, c + 3);
  int mm = *min_element(m, m + 3);
  int ym = *min_element(y, y + 3);
  int km = *min_element(k, k + 3);

  if (cm + mm + ym + km < 1e6) return cout << "IMPOSSIBLE\n", void();

  int rem = 1e6;
  for (int i : {cm, mm, ym, km}) {
    cout << min(rem, i) << ' ';
    rem -= min(rem, i);
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
