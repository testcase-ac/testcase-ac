#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 10000;
ll a[MAX];
pll v[MAX];

void solve() {
  int n, k;
  ll t1, t2;
  cin >> n >> k >> t1 >> t2;
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < k; i++) cin >> v[i].first >> v[i].second;

  vector<pll> intervals;
  for (int i = 0; i < n; i++) {
    // Calculate impossible intervals
    for (int j = 0; j < k; j++) {
      auto [bj, ej] = v[j];
      ll bi = max(bj - a[i], t1), ei = min(ej - a[i], t2);
      if (bi <= t2 && ei >= t1) intervals.push_back({bi, ei});
    }
  }
  sort(intervals.begin(), intervals.end());

  ll tsum = t2 - t1, asum = 0;
  ll cs = -1e18, ce = -1e18;
  for (auto [as, ae] : intervals) {
    if (ce < as) {
      asum += (ce - cs);
      cs = as;
      ce = ae;
    }
    else ce = max(ae, ce);
  }
  asum += (ce - cs);

  double n1 = tsum - asum, n2 = tsum;
  cout << fixed << setprecision(10) << n1 / n2 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
