#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 300, MAXV = 150'000;
int w[MAX + 1];
bool dl[MAX + 5][MAXV + 1], dr[MAX + 5][MAXV + 1];

void solve() {
  int n;
  cin >> n;

  int sum = 0;
  for (int i = 1; i <= n; i++) cin >> w[i], sum += w[i];

  dl[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= MAXV; j++) dl[i][j] = dl[i - 1][j];
    for (int j = 0; j <= MAXV; j++) {
      if (dl[i - 1][j] && j + w[i] <= MAXV) dl[i][j + w[i]] = 1;
    }
  }

  dr[n + 1][0] = 1;
  for (int i = n; i >= 1; i--) {
    for (int j = 0; j <= MAXV; j++) dr[i][j] = dr[i + 1][j];
    for (int j = 0; j <= MAXV; j++) {
      if (dr[i + 1][j] && j + w[i] <= MAXV) dr[i][j + w[i]] = 1;
    }
  }

  vector<int> ans;
  for (int i = 1; i <= n; i++) {
    if ((sum - w[i]) & 1) continue;

    for (int l = 0; l <= MAXV; l++) {
      int r = (sum - w[i]) / 2 - l;

      if (!dl[i - 1][l]) continue;
      if (r < 0) continue;
      if (!dr[i + 1][r]) continue;

      ans.push_back(i);
      break;
    }
  }

  cout << ans.size() << '\n';
  for (int e : ans) cout << e << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
