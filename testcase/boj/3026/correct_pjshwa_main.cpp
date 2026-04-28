#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MAX = 1e5;
bool ds[10];
ll x, a, b, d[13][MAX][2];

ll r(int n, ll pfx) {
  ll mx = pfx, mn = pfx;
  for (int i = 0; i < n; i++) mx = mx * 10 + 9;
  for (int i = 0; i < n; i++) mn = mn * 10;

  if (mx < a || mn > b) return 0;
  if (n == 0) return pfx % x == 0;

  bool allBetween = mn >= a && mx <= b;
  if (allBetween && d[n][pfx % x][pfx == 0] != -1) return d[n][pfx % x][pfx == 0];

  ll ans = 0;
  for (int g = 0; g < 10; g++) if (ds[g]) ans += r(n - 1, pfx * 10 + g);
  if (!ds[0] && pfx == 0) ans += r(n - 1, 0);

  if (allBetween) d[n][pfx % x][pfx == 0] = ans;
  return ans;
}

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  string s;
  cin >> x >> a >> b >> s;
  for (char c : s) ds[c - '0'] = true;
  memset(d, -1, sizeof(d));

  ll cnt = 0, cx;
  if (x >= MAX) {
    bool able;
    for (ll xi = x; xi <= b; xi += x) {
      if (xi < a) continue;
      able = true;
      cx = xi;

      while (cx) {
        able &= ds[cx % 10];
        cx /= 10;
      }

      if (able) cnt++;
    }
  }
  else cnt = r(12, 0);
  cout << cnt;
}
