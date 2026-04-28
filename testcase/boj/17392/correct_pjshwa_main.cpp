#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M; cin >> N >> M;

  int K = 0;
  for (int i = 1; i <= N; i++) {
    int x; cin >> x;
    K += x + 1;
  }
  if (K >= M) cout << "0\n";
  else {
    K = M - K;
    vector<int> S(N + 1, K / (N + 1));
    for (int i = 0; i < K % (N + 1); i++) S[i]++;

    ll ans = 0;
    for (int i = 0; i < N + 1; i++) {
      ll u = S[i];
      ans += u * (u + 1) * (2 * u + 1) / 6;
    }
    cout << ans << '\n';
  }

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
