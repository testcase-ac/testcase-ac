#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  ll N, K; cin >> N >> K;
  vector<tuple<ll, ll, ll>> A;
  for (int i = 0; i < N; ++i) {
    ll ci, ti, si; cin >> ci >> ti >> si;
    A.emplace_back(ti, ci, si);
  }
  sort(A.begin(), A.end(), greater<>());

  ll ans = 0, i = 0;
  priority_queue<pair<ll, ll>> pq;
  while (K) {
    while (i < N) {
      auto& [ti, ci, si] = A[i];
      if (ti < K) break;
      pq.emplace(si, ci);
      ++i;
    }

    ll nK = i == N ? 0 : get<0>(A[i]);
    ll g = K - nK;

    while (g && !pq.empty()) {
      auto [si, ci] = pq.top(); pq.pop();
      ll take = min(g, ci);
      ans += take * si;

      ci -= take; g -= take;
      if (ci) pq.emplace(si, ci);
    }

    K = nK;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
