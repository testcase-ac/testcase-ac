#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 36;
ll d[MAX + 1];
int mg[5], xg[5];

int r(char c) {
  if (c == 'B') return 0;
  if (c == 'S') return 1;
  if (c == 'G') return 2;
  if (c == 'P') return 3;
  if (c == 'D') return 4;
}

void solve() {
  int n, P[4];
  string s;
  cin >> n >> P[0] >> P[1] >> P[2] >> P[3] >> s;
  for (int i = 0; i < 4; i++) {
    xg[i] = P[i] - 1;
    mg[i + 1] = P[i];
  }
  xg[4] = P[3] * 2;

  d[0] = s[0] == 'D' ? P[3] : xg[r(s[0])];
  for (int i = 1; i < n; i++) {
    if (s[i] == 'D') {
      d[i] = P[3];
      continue;
    }
    
    if (d[i - 1] + d[i] < xg[r(s[i])]) d[i] = xg[r(s[i])] - d[i - 1];
    else if (d[i - 1] + d[i] > xg[r(s[i])]) {
      d[i] = 0;
      d[i - 1] = xg[r(s[i])];
      for (int j = i - 1; j > 0; j--) {
        if (d[j] + d[j - 1] < mg[r(s[j])]) d[j - 1] = mg[r(s[j])] - d[j];
        else if (d[j] + d[j - 1] > xg[r(s[j])]) d[j - 1] = xg[r(s[j])] - d[j];
        else break;
      }
    }
  }

  cout << accumulate(d, d + n, 0LL) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
