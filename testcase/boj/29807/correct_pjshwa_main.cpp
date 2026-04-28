#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  int S[5]{};
  for (int i = 0; i < N; ++i) cin >> S[i];

  int V1 = S[0] > S[2] ? 508 * (S[0] - S[2]) : 108 * (S[2] - S[0]);
  int V2 = S[1] > S[3] ? 212 * (S[1] - S[3]) : 305 * (S[3] - S[1]);
  int V3 = S[4] * 707;

  int ans = (V1 + V2 + V3) * 4763;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
