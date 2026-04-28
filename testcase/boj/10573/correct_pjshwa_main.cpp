#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int n;
string s;
ll d[2][10][100];

ll r(int f, int t, int g) {
  if (g == n) return 1;
  if (d[f][t][g] != -1) return d[f][t][g];

  ll res = 0;
  if (f) {
    for (int i = t; i <= s[g] - '0'; i++) res += r(f && i == (s[g] - '0'), i, g + 1);
  }
  else {
    for (int i = t; i <= 9; i++) res += r(f, i, g + 1);
  }

  return d[f][t][g] = res;
}

void solve() {
  cin >> s;
  n = s.size();

  memset(d, -1, sizeof(d));

  for (int i = 0; i < n - 1; i++) {
    if (s[i] > s[i + 1]) return cout << "-1\n", void();
  }

  ll ans = 0;
  for (int i = 0; i < s[0] - '0'; i++) ans += r(0, i, 1);
  ans += r(1, s[0] - '0', 1);

  cout << ans - 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
