#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
int D[MAXN + 1], P[MAXN + 1];

void solve() {
  int n, t; cin >> n >> t;

  vector<pii> ws;
  for (int i = 1; i <= n; ++i) {
    int w; cin >> w;
    ws.emplace_back(w, i);
  }
  sort(ws.begin(), ws.end());

  for (int i = 1; i <= n; ++i) cin >> D[i];
  for (int i = 1; i <= n; ++i) cin >> P[i];
  vector<pair<ll, int>> pfts;
  for (int i = 1; i <= n; ++i) {
    ll pft = P[i] - (ll)D[i] * t;
    pfts.emplace_back(pft, i);
  }
  sort(pfts.begin(), pfts.end());

  vector<int> ans(n + 1);
  for (int i = 0; i < n; ++i) {
    ans[pfts[i].second] = ws[i].second;
  }
  for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
