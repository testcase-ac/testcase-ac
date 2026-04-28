#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 10000, INF = 1e9 + 7;
int d[10][MAX], n;
string s, t;

int r(int l, int i) {
  if (i == n) return 0;
  if (d[l][i] != -1) return d[l][i];

  int src = s[i] - '0', dst = t[i] - '0';
  src = (src + l) % 10;

  int diff = (dst - src + 10) % 10, res = INF;
  for (int a = 0; a < 10; a++) {
    int b = (diff - a + 10) % 10;
    b = (10 - b) % 10;

    res = min(res, r((l + a) % 10, i + 1) + a + b);
  }

  return d[l][i] = res;
}

void solve() {
  cin >> n >> s >> t;

  memset(d, -1, sizeof(d));
  cout << r(0, 0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
