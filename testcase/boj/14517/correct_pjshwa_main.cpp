#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000, MOD = 10007;
int d[MAX][MAX];
string s;

int rec(int l, int r) {
  if (d[l][r] != -1) return d[l][r];
  if (l == r) return d[l][r] = 1;
  if (l > r) return d[l][r] = 0;
  
  int res = rec(l + 1, r) + rec(l, r - 1) + (MOD - rec(l + 1, r - 1));
  if (s[l] == s[r]) res += rec(l + 1, r - 1) + 1;
  return d[l][r] = res % MOD;
}

void solve() {
  cin >> s;
  memset(d, -1, sizeof(d));
  cout << rec(0, s.size() - 1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
