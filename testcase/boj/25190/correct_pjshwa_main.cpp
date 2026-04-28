#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAXN = 1000, MAXV = 3200;
pii a[MAXN + 1];
int d[2][MAXV + 1];

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i].first >> a[i].second;
  sort(a + 1, a + n + 1, [](pii a, pii b) {
    return a.first + a.second < b.first + b.second;
  });

  for (int i = 1; i <= n; i++) {
    int x = i & 1;
    for (int j = 0; j <= MAXV; j++) d[x][j] = d[1 - x][j];
    for (int j = 0; j < a[i].second; j++) {
      int nv = min(MAXV, j + a[i].first);
      d[x][nv] = max(d[x][nv], d[1 - x][j] + 1);
    }
  }

  int x = n & 1, mv = 0;
  for (int j = 0; j <= MAXV; j++) {
    if (d[x][j] > mv) mv = d[x][j];
  }
  int con = MAXV;
  for (int j = MAXV; j >= 0; j--) {
    if (d[x][j] == mv) con = j;
  }

  cout << mv << ' ' << con << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
