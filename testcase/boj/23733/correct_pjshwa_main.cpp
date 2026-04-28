#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAXN = 18, MAXK = 18;

ll pw10[MAXN + 1];

// d[n][k]: largest sum obtainable if we chose k digits as one subnumber from last n digits
ll d[MAXN + 1][MAXK + 1];

void solve() {
  int n, k; string s;
  cin >> n >> k >> s;
  reverse(s.begin(), s.end());

  memset(d, 0, sizeof(d));
  d[1][0] = d[1][1] = s[0] - '0';
  for (int i = 2; i <= n; i++) for (int j = 0; j <= i; j++) {
    ll dig = s[i - 1] - '0';
    if (j < i) d[i][j] = d[i - 1][j] + pw10[i - j - 1] * dig;
    if (j) d[i][j] = max(d[i][j], d[i - 1][j - 1] + pw10[j - 1] * dig);
  }

  cout << d[n][k] << '\n';
}

int main() {
  fast_io();

  pw10[0] = 1;
  for (int i = 1; i <= MAXN; i++) pw10[i] = pw10[i - 1] * 10;

  int t = 1;
  cin >> t;
  while (t--) solve();
}
