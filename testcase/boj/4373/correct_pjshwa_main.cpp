#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000, INF = 2e9;
ll a[MAX], n;

void solve() {
  map<int, int> t;
  for (int i = 0; i < n; i++) cin >> a[i], t[a[i]]++;

  vector<pair<int, pii>> vl, vr;
  for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) {
    vl.push_back({a[i] + a[j], {i, j}});
    vr.push_back({a[i] - a[j], {i, j}});
    vr.push_back({a[j] - a[i], {i, j}});
  }
  sort(vl.begin(), vl.end());
  sort(vr.begin(), vr.end());
  reverse(vr.begin(), vr.end());

  ll pt = 0, ans = -INF;
  for (auto& [e, p1] : vl) {
    while (pt < vr.size() && e + vr[pt].first > 0) pt++;

    while (pt < vr.size() && e + vr[pt].first == 0) {
      auto& [i, j] = p1;
      auto& [k, l] = vr[pt].second;
      set<int> u = {i, j, k, l};
      if (u.size() == 4) {
        if (a[i] + a[j] + a[k] == a[l]) ans = max(ans, a[l]);
        if (a[i] + a[j] + a[l] == a[k]) ans = max(ans, a[k]);
      }
      pt++;
    }
  }

  if (ans == -INF) cout << "no solution\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  while (1) {
    cin >> n;
    if (n == 0) break;
    solve();
  }
}
