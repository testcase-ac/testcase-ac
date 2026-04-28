#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50, INF = 1e9 + 7;
string u;
int n;
int d[MAX + 1][MAX + 1];

int rec(int l, int r) {
  if (d[l][r] != -1) return d[l][r];
  if (l > r) return d[l][r] = 0;

  if (u[l] == u[r]) return d[l][r] = rec(l + 1, r - 1);
  else {
    int res = INF;
    res = min(res, rec(l + 1, r) + 1);
    res = min(res, rec(l, r - 1) + 1);
    res = min(res, rec(l + 1, r - 1) + 1);
    return d[l][r] = res;
  }
}

int solve(string s) {
  u = s;
  int n = s.size();
  memset(d, -1, sizeof d);
  return rec(0, n - 1);
}

void solve() {
  string s;
  cin >> s;
  int n = s.size();

  int ans = solve(s);
  for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) {
    string t = s;
    swap(t[i], t[j]);
    ans = min(ans, solve(t) + 1);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
