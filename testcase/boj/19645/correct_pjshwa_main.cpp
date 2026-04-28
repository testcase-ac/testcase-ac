#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAXN = 50, MAXV = 2500;
int a[MAXN];
bool d[MAXV + 1][MAXV + 1];

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  int s = accumulate(a, a + n, 0);

  d[0][0] = true;
  for (int i = 0; i < n; i++) for (int j = s; j >= 0; j--) for (int k = s; k >= 0; k--) {
    if (j >= a[i]) d[j][k] |= d[j - a[i]][k];
    if (k >= a[i]) d[j][k] |= d[j][k - a[i]];
  }

  int ans = 0;
  for (int j = 0; j <= s; j++) for (int k = 0; k <= s; k++) {
    if (!d[j][k]) continue;
    int l = s - j - k;
    if (l <= j && l <= k) ans = max(ans, l);
  }

  cout << ans << '\n';
}
