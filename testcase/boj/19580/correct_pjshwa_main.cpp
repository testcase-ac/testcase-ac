#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int N, M;
  cin >> N >> M;

  vector<pll> A(N), T(M);
  for (int i = 0; i < N; i++) cin >> A[i].first >> A[i].second;
  for (int i = 0; i < M; i++) cin >> T[i].first >> T[i].second;
  sort(A.begin(), A.end());
  sort(T.begin(), T.end());

  priority_queue<pll> pq;
  int ans = 0, ni = 0;
  for (int i = 0; i < M; i++) {
    auto [pi, xi] = T[i];
    while (ni < N && A[ni].first <= pi) {
      auto [li, ri] = A[ni];
      pq.push({-ri, li});
      ni++;
    }

    while (xi && !pq.empty()) {
      auto [ri, li] = pq.top();
      ri = -ri;
      pq.pop();

      if (li <= pi && pi <= ri) {
        ans++;
        xi--;
      }
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
