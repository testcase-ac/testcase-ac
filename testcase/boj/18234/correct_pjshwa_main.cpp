#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int N, T;
  cin >> N >> T;
  vector<pii> A(N);
  for (int i = 0; i < N; i++) cin >> A[i].second >> A[i].first;
  sort(A.begin(), A.end());
  reverse(A.begin(), A.end());

  ll ans = 0;
  for (int i = 1; i <= N; i++) {
    ll mul = T - i;
    ll cur = mul * A[i - 1].first + A[i - 1].second;
    ans += cur;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
