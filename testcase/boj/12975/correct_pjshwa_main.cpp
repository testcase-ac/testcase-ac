#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAXN = 100, MAXV = 255;
int a[MAXN];
bool d[MAXV + 1][MAXV + 1], dt[MAXV + 1][MAXV + 1];

int main() {
  fast_io();

  int n, s = 0;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i], s ^= a[i];

  d[0][0] = true;
  for (int i = 0; i < n; i++) {
    memset(dt, 0, sizeof(dt));
    for (int j = 0; j <= MAXV; j++) for (int k = 0; k <= MAXV; k++) {
      dt[j][k] |= d[j ^ a[i]][k];
      dt[j][k] |= d[j][k ^ a[i]];
    }
    for (int j = 0; j <= MAXV; j++) for (int k = 0; k <= MAXV; k++) d[j][k] |= dt[j][k];
  }

  int ans = 0;
  for (int j = 0; j <= MAXV; j++) for (int k = 0; k <= MAXV; k++) {
    if (!d[j][k]) continue;
    ans = max(ans, j + k + (s ^ j ^ k));
  }

  cout << ans << '\n';
}
