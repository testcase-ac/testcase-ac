#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 500, INF = 1e9 + 7;
int d[MAX][MAX];
string s;

int rec(int l, int r) {
  if (d[l][r] != -1) return d[l][r];
  if (l == r) return d[l][r] = 0;
  if (r == l + 1) {
    if (s[l] == 'a' && s[r] == 't') return d[l][r] = 2;
    if (s[l] == 'g' && s[r] == 'c') return d[l][r] = 2;
    return d[l][r] = 0;
  }

  int res = 0;
  if (s[l] == 'a' && s[r] == 't') res = max(res, rec(l + 1, r - 1) + 2);
  if (s[l] == 'g' && s[r] == 'c') res = max(res, rec(l + 1, r - 1) + 2);
  for (int j = l + 1; j <= r; j++) res = max(res, rec(l, j - 1) + rec(j, r));
  
  return d[l][r] = res;
}

void solve() {
  cin >> s;
  int n = s.size();
  memset(d, -1, sizeof(d));
  cout << rec(0, n - 1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
