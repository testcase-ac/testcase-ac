#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int N;
  cin >> N;
  vector<pll> A(N);
  for (int i = 0; i < N; i++) {
    cin >> A[i].first >> A[i].second;
  }
  sort(A.begin(), A.end());

  ll ans = 0;
  for (int i = 0; i < N; i++) {
    auto [ai, bi] = A[i];
    ans += ai * (i + 1) + bi;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
