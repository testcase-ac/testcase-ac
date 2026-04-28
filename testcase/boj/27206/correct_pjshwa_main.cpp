#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  vector<pii> A;
  for (int i = 0; i < N; i++) {
    int a, b; cin >> a >> b;
    A.push_back({a, b});
  }
  sort(A.begin(), A.end(), [](pii a, pii b) {
    return a.second < b.second;
  });

  priority_queue<pii, vector<pii>, greater<pii>> pq;
  for (int i = 0; i < N; i++) {
    auto [a, b] = A[i];
    pq.push({a + b, i});
  }

  int ans = 0x3f3f3f3f;
  for (int i = 0; i < N; i++) {
    auto [a, b] = A[i];
    while (pq.size() >= 2) {
      auto [v1, i1] = pq.top(); pq.pop();
      auto [v2, i2] = pq.top(); pq.pop();

      if (i1 > i && i2 > i) {
        ans = min(ans, v1 + v2 + a);
        pq.push({v1, i1}); pq.push({v2, i2});
        break;
      }
      else {
        if (i1 > i) pq.push({v1, i1});
        if (i2 > i) pq.push({v2, i2});
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
