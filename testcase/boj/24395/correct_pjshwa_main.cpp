#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100, INF = 1e9 + 7;
int rp[MAX], bp[MAX], v[MAX];
int d[51][51][MAX + 1];

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; i++) cin >> rp[i] >> bp[i] >> v[i];

  for (int i = 0; i <= m; i++) for (int ri = 0; ri <= 50; ri++) for (int bi = 0; bi <= 50; bi++) {
    d[ri][bi][i] = -INF;
  }

  d[0][0][0] = 0;
  for (int i = 1; i <= m; i++) {
    for (int ri = 0; ri <= 50; ri++) for (int bi = 0; bi <= 50; bi++) {
      d[ri][bi][i] = d[ri][bi][i - 1];
      if (ri < rp[i - 1] || bi < bp[i - 1]) continue;
      int prev = d[ri - rp[i - 1]][bi - bp[i - 1]][i - 1];
      if (prev != -INF) d[ri][bi][i] = max(d[ri][bi][i], prev + v[i - 1]);
    }
  }

  vector<pii> ans;
  for (int i = 1; i <= n; i++) {
    int ri, bi;
    cin >> ri >> bi;

    if (d[ri][bi][m] == -INF) ans.push_back({0, i});
    else ans.push_back({d[ri][bi][m], i});
  }
  sort(ans.begin(), ans.end());

  for (auto p : ans) cout << p.second << ' ' << p.first << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
