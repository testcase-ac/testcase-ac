#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 300, MOD = 1e9 + 7;
int d[MAX + 1][MAX + 1];
string s;

int r(int si, int ei) {
  if (d[si][ei] != -1) return d[si][ei];

  ll ans;
  if (si > ei) ans = 1;
  else {
    ans = 0;
    for (int k = si + 1; k <= ei; k++) {
      if (s[si] != s[k]) ans = (ans + (ll)r(si + 1, k - 1) * r(k + 1, ei)) % MOD;
    }
  }

  return d[si][ei] = ans;
}

int main() {
  fast_io();

  cin >> s;
  memset(d, -1, sizeof(d));
  cout << r(0, s.size() - 1) << '\n';
}
