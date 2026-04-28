#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 300;
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
ll a[MAX][MAX], d[MAX][MAX];
int n, m;

ll r(int i, int j) {
  if (d[i][j] != -1) return d[i][j];

  ll ret = 0;
  for (int k = 0; k < 4; k++) {
    int x = i + dx[k], y = j + dy[k];
    if (x < 0 || x >= n || y < 0 || y >= m) continue;
    if (a[x][y] > a[i][j]) ret += r(x, y);
  }

  return d[i][j] = ret + 1;
}

void solve() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> a[i][j];

  vector<int> ans(n * m + 1);
  memset(d, -1, sizeof(d));
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    ans[a[i][j]] = r(i, j);
  }

  for (int i = 1; i <= n * m; i++) cout << ans[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
