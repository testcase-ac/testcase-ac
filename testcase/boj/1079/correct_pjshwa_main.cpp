#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 20;
int w[MAX], r[MAX][MAX];
bool killed[MAX];
int n, p, ans, cur;

void dfs_night() {
  cur++;
  for (int i = 0; i < n; i++) {
    if (killed[i]) continue;

    // Night
    killed[i] = 1;
    for (int j = 0; j < n; j++) {
      if (!killed[j]) w[j] += r[i][j];
    }

    // Day
    int k = -1, m = -1e9;
    for (int j = 0; j < n; j++) {
      if (!killed[j] && w[j] > m) k = j, m = w[j];
    }

    if (k == p) ans = max(ans, cur);
    else {
      killed[k] = 1;
      dfs_night();
      killed[k] = 0;
    }

    // Night reverse
    for (int j = 0; j < n; j++) {
      if (!killed[j]) w[j] -= r[i][j];
    }
    killed[i] = 0;
  }
  cur--;
}

void dfs_day() {
  // Day
  int k = -1, m = -1e9;
  for (int j = 0; j < n; j++) {
    if (!killed[j] && w[j] > m) k = j, m = w[j];
  }

  if (k == p) ans = max(ans, cur);
  else {
    killed[k] = 1;

    // Night
    for (int i = 0; i < n; i++) {
      if (killed[i]) continue;

      killed[i] = 1;
      for (int j = 0; j < n; j++) {
        if (!killed[j]) w[j] += r[i][j];
      }

      cur++;
      dfs_day();
      cur--;

      for (int j = 0; j < n; j++) {
        if (!killed[j]) w[j] -= r[i][j];
      }
      killed[i] = 0;
    }
    killed[k] = 0;
  }
}

void solve() {
  cin >> n;
  for (int i = 0; i < n; i++) cin >> w[i];
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> r[i][j];
  cin >> p;

  if (n & 1) dfs_day();
  else dfs_night();
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
