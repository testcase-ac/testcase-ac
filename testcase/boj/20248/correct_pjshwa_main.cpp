#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const double EPS = 1e-7;

void solve() {
  int n;
  cin >> n;
  vector<pii> a(n);
  for (int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;

  using t = tuple<double, int, int>;
  priority_queue<t, vector<t>, greater<t>> pq;
  for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) {
    double d = hypot(a[i].first - a[j].first, a[i].second - a[j].second);
    pq.emplace(d / 2, i, j);
  }

  vector<double> vis(n, -1);
  while (!pq.empty()) {
    auto [d, i, j] = pq.top(); pq.pop();
    if (vis[i] != -1 && vis[j] != -1) continue;

    if (vis[i] == -1 && vis[j] == -1) {
      vis[i] = vis[j] = d;
      for (int l = 0; l < n; l++) {
        if (vis[l] != -1) continue;
        double id = hypot(a[i].first - a[l].first, a[i].second - a[l].second);
        double jd = hypot(a[j].first - a[l].first, a[j].second - a[l].second);
        pq.emplace(id - vis[i], i, l);
        pq.emplace(jd - vis[j], j, l);
      }
    }
    else {
      int k;
      double g = hypot(a[i].first - a[j].first, a[i].second - a[j].second);

      if (vis[i] == -1) {
        k = i;
        if (abs(vis[j] + d - g) > EPS) continue;
      }
      else {
        k = j;
        if (abs(vis[i] + d - g) > EPS) continue;
      }

      vis[k] = d;
      for (int l = 0; l < n; l++) {
        if (vis[l] != -1) continue;
        double kd = hypot(a[k].first - a[l].first, a[k].second - a[l].second);
        pq.emplace(kd - vis[k], k, l);
      }
    }
  }

  double ans = 0;
  for (int i = 0; i < n; i++) ans += M_PI * vis[i] * vis[i];
  cout << fixed << setprecision(10) << ans << '\n';
}

int main() {
  fast_io();
 
  int t = 1;
  // cin >> t;
  while (t--) solve();
}
