#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 3000, INF = 1e9 + 7;
int d[MAX + 1][2];

bool is_lower(char c) {
  return c >= 'a' && c <= 'z';
}

void solve() {
  string s;
  cin >> s;

  int n = s.size();
  d[0][1] = 1;
  for (int i = 1; i <= n; i++) {
    if (is_lower(s[i - 1])) {
      d[i][0] = d[i - 1][0] + 1;
      d[i][1] = min(d[i - 1][1], d[i - 1][0]) + 2;
    }
    else {
      d[i][0] = min(d[i - 1][0], d[i - 1][1]) + 2;
      d[i][1] = d[i - 1][1] + 1;
    }
  }

  cout << min(d[n][0], d[n][1]) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
