#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  vector<int> L(N);
  for (int i = 0; i < N; i++) cin >> L[i];
  sort(L.begin(), L.end(), greater<>());

  int ans = 0;
  for (int i = 1; i < N; i++) ans += L[0] + L[i];
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
