#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
int S[MAXN + 1];

void solve() {
  int N, M; cin >> N >> M;
  while (M--) {
    int u, v; cin >> u >> v;
    ++S[u];
  }
  sort(S + 1, S + N + 1);

  ll ans = 0;
  for (int i = 2; i <= N; ++i) {
    ll t = S[i - 1] + 1;
    if (t > S[i]) {
      ll d = t - S[i];
      ans += d;
      S[i] += d;
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
