#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
int d[MAX + 1][MAX + 1];
string s, t;

int r(int n, int m) {
  if (n == 0) return m;
  if (m == 0) return n;
  if (d[n][m] != -1) return d[n][m];

  int res = r(n - 1, m) + 1;
  res = min(res, r(n, m - 1) + 1);
  res = min(res, r(n - 1, m - 1) + (s[n - 1] == t[m - 1] ? 0 : 1));
  return d[n][m] = res;
}

void solve() {
  cin >> s >> t;
  memset(d, -1, sizeof(d));
  cout << r(s.size(), t.size()) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
