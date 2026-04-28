#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXS = 2000, INF = 1e18;
ll dp[MAXS + 1];
vector<ll> Vs[MAXS + 1];

void solve() {
  ll S, N; cin >> S >> N;
  for (int i = 0; i < N; ++i) {
    ll v, w, k, pw = 1, sum = 0; cin >> v >> w >> k;
    while (sum + pw <= k) {
      ll value = v * pw, weight = w * pw;
      if (weight <= S) Vs[weight].push_back(value);
      sum += pw; pw <<= 1;
    }
    if (sum < k) {
      ll value = v * (k - sum), weight = w * (k - sum);
      if (weight <= S) Vs[weight].push_back(value);
    }
  }
  for (int w = 1; w <= S; ++w) {
    sort(Vs[w].begin(), Vs[w].end(), greater<ll>());
    while (!Vs[w].empty() && (ll)Vs[w].size() * w > S) Vs[w].pop_back();
  }

  fill(dp, dp + S + 1, -INF); dp[0] = 0;
  for (int w = 1; w <= S; ++w) for (ll v : Vs[w]) {
    for (int i = S; i >= w; --i) dp[i] = max(dp[i], dp[i - w] + v);
  }
  cout << *max_element(dp, dp + S + 1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
