#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 3000;
const ll INF = 1e18;
int a[MAX];
ll d[MAX + 1][MAX + 1][4];
vector<int> r;
int n, x, y, z;

ll rec(int i, int j, int f) {
  if (i > j) return f == 0 ? 0 : INF;
  if (d[i][j][f] != -1) return d[i][j][f];

  ll ret = INF;

  // Use x
  if (i < j) {
    ret = min(ret, rec(i + 2, j, f == 1 ? 3 : f) + (ll)x * (r[i + 1] - r[i]));
    ret = min(ret, rec(i, j - 2, f == 2 ? 3 : f) + (ll)x * (r[j] - r[j - 1]));
  }

  // reserve for y
  if (f == 0) {
    ret = min(ret, rec(i + 1, j, 1));
    ret = min(ret, rec(i, j - 1, 2));
  }
  if (f == 1) {
    if (r[i - 1] + 1 == r[i]) ret = min(ret, rec(i + 1, j, 0) + 2 * y);
    else ret = min(ret, rec(i + 1, j, 0) + y);

    if (r[i - 1] + 1 == r[j]) ret = min(ret, rec(i, j - 1, 0) + 2 * y);
    else ret = min(ret, rec(i, j - 1, 0) + y);
  }
  if (f == 2) {
    if (r[i] + 1 == r[j + 1]) ret = min(ret, rec(i + 1, j, 0) + 2 * y);
    else ret = min(ret, rec(i + 1, j, 0) + y);

    if (r[j] + 1 == r[j + 1]) ret = min(ret, rec(i, j - 1, 0) + 2 * y);
    else ret = min(ret, rec(i, j - 1, 0) + y);
  }
  if (f == 3) {
    ret = min(ret, rec(i + 1, j, 0) + y);
    ret = min(ret, rec(i, j - 1, 0) + y);
  }

  return d[i][j][f] = ret;
}

void solve() {
  string s, t;
  cin >> n >> x >> y >> s >> t;

  memset(a, 0, sizeof(a));

  int oz = 0;
  for (int i = 0; i < n; i++) {
    if (s[i] == '1') a[i] ^= 1;
    if (t[i] == '1') a[i] ^= 1;
    if (a[i]) oz++;
  }
  if (oz & 1) return cout << "-1\n", void();

  r.clear();
  for (int i = 0; i < n; i++) {
    if (a[i] == 0) continue;
    r.push_back(i);
  }

  // if (r.size() == 2) {
  //   if (r[0] + 1 == r[1]) cout << min(x, 2 * y) << '\n';
  //   else cout << min((r[1] - r[0]) * x, y) << '\n';
  //   return;
  // }

  z = r.size();
  for (int i = 0; i < z; i++) for (int j = 0; j < z; j++) {
    d[i][j][0] = d[i][j][1] = d[i][j][2] = d[i][j][3] = -1;
  }
  cout << rec(0, z - 1, 0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
