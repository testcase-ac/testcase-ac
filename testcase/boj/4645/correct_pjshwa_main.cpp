#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int dp[7][65][65][65][2];
int hilbert(int x, int s, int e, int d, int o) {
  if (s > e) return 0;
  if (x < 7 && dp[x][s][e][d][o] != -1) return dp[x][s][e][d][o];
  int ans;

  if (x == 1) {
    if (o == 0) ans = d == 1 ? e - s : 0;
    else ans = d == 1 && s <= 1 && 2 <= e;
  }
  else {
    int n = 1 << x, h = n / 2;
    if (o == 0) {
      if (d == h) {
        int cnt = 0;
        if (s <= 0 && 1 <= e) cnt++;
        if (s <= n - 1 && n <= e) cnt++;
        ans = cnt;
      }
      else if (d < h) ans = hilbert(x - 1, s, min(h, e), h - d, 1) + hilbert(x - 1, n - e, h - max(0, s - h), d, 1);
      else ans = hilbert(x - 1, s, min(h, e), d - h, 0) + hilbert(x - 1, max(s, h) - h, e - h, d - h, 0);
    }
    else {
      if (d == h) ans = s <= h && h + 1 <= e;
      else if (d < h) ans = hilbert(x - 1, max(0, h - e), h - s, d, 0) + hilbert(x - 1, max(0, s - h), e - h, d, 1);
      else ans = hilbert(x - 1, s, min(h, e), n - d, 0) + hilbert(x - 1, max(0, s - h), e - h, d - h, 1);
    }
  }

  if (x < 7) dp[x][s][e][d][o] = ans;
  return ans;
}

int main() {
  fast_io();

  while (1) {
    int n, x1, x2, y;
    cin >> n;
    if (n == 0) break;
    memset(dp, -1, sizeof(dp));

    cin >> x1 >> x2 >> y;
    cout << hilbert(n, x1, x2, (1 << n) - y, 0) << '\n';
  }
}
