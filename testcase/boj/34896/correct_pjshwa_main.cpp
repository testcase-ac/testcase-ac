#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, B; cin >> N;
  vector<pii> A(N);
  for (int i = 0; i < N; ++i) cin >> A[i].first;
  for (int i = 0; i < N; ++i) cin >> A[i].second;
  sort(A.begin(), A.end());
  cin >> B;

  ll l = 1, r = 2e8 + 1;
  while (l < r) {
    ll m = (l + r) / 2, total = 0;
    int cost = A[0].second;
    for (int i = 1; i < N; ++i) {
      auto [x, c] = A[i];
      if (x - A[i - 1].first <= m) cost = min(cost, c);
      else total += cost, cost = c;
    }
    if (total + cost <= B) r = m;
    else l = m + 1;
  }

  cout << l << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
