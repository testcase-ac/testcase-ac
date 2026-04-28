#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100, MAXV = 1e6;
int l[MAX + 1];
bool d[2][MAXV + 1];

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> l[i];

  d[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    int x = i & 1;

    for (int v = 0; v <= MAXV; v++) d[x][v] = d[1 - x][v];
    for (int v = l[i]; v <= MAXV; v++) d[x][v] |= d[1 - x][v - l[i]];
  }

  ll rsum = 0, rcnt = 0;
  for (int v = 0; v <= MAXV; v++) {
    if (d[n & 1][v]) {
      rsum += v + 1;
      rcnt++;
    }
  }

  ll ans = 2 * rsum - rcnt * (rcnt + 1) / 2;
  cout << ans << '\n';
}

int main() {
  fast_io();
 
  int t = 1;
  // cin >> t;
  while (t--) solve();
}
